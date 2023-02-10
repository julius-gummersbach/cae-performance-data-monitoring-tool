//
// Created by CAE-DUALSTUDIS on 03.02.2023.
//
#include "Controller.hpp"

#include <utility>
#include "string"
#include "thread"
#include "chrono"
#include "sstream"

using std::string;
using std::stringstream;
using json = nlohmann::json;

namespace CAEMonitoringTool {
    typedef websocketpp::server<websocketpp::config::asio> server;

    void Controller::startUp() {
        //DataParser m_dataParser;
        DataStore::DataManager& dataManager = m_dataManager;
        DataProcessing::GraphManager& graphManager = m_graphManager;


        // Configures the (client) endpoint and sets up a connection between it and the data Server
        CAEMonitoringTool::Websocket::WebsocketEndpoint endpoint;
        int dataConId = endpoint.connect("ws://localhost:5000");
        // Waits for the connection to establish and sends a message to the dataServer
        // to let it know to start sending its data (JSON-Strings)
        while(endpoint.getMetadata(dataConId)->getStatus() != "Open"){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        endpoint.send(dataConId, "startData");
        bool isDone{false}; //TODO false
        int i{0};
        while (!isDone) {
            // Checks the message content. If it is not empty, it parses the string into a JSON object.
            // The return value of parseThreadInfo is a boolean determined by a JSON field of the string.
            // If it equals true, that means that this was the last message to be received and the loop can be stopped.
            string mes = endpoint.getMessage(dataConId);
            if (!mes.empty()) {
                std::cout << "received message " << ++i << std::endl;
                isDone = DataProcessing::DataParser::parseThreadInfo(mes, dataManager, graphManager);
                std::cout << "parsed message " << i << std::endl;
            } else {
                // If the message content is empty, that means the next message has not been received yet,
                // and we need to wait for that.
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        //guiServer.set_message_handler(&on_message);

        server guiServer;
        websocketpp::connection_hdl guiHdl{};
        guiServer.set_open_handler(
                [&guiHdl, &guiServer, &dataManager](websocketpp::connection_hdl hdl) -> void {
                    guiHdl = std::move(hdl);
                    std::cout << "Gui connection established!" << std::endl;
                    // Get initial Threads to gui
                    auto guiConnection = guiServer.get_con_from_hdl(guiHdl);
                    json payload;
                    for (const auto &threadId: dataManager.getThreadIds()) {
                        payload.push_back({{"tid",threadId},{"name",json::parse(dataManager.getThreadInfo(threadId)).at("name")}});
                    }
                    json msg{{"sender","server"},
                             {"topic","startup"},
                             {"payload", payload.dump()}};
                    guiConnection->send(msg.dump());
                });
        // This method gets called for both incoming and outgoing messages
        guiServer.set_message_handler(
                [&guiServer, &guiHdl, &graphManager, &dataManager]
                        (websocketpp::connection_hdl h, const server::message_ptr &msg) -> void {
                    json messageJson = json::parse(msg->get_payload());
                    if(messageJson.at("sender") == "gui"){
                        if(messageJson.at("topic") == "requestData"){
                            string threadId = messageJson.at("payload").at("tid");

                            string payloadString = dataManager.getThreadInfo(threadId);
                            json payload;
                            if(payloadString.empty()){
                                payload["tid"] = threadId;
                                payload["modules"] = std::vector<string>();
                            } else {
                                payload = json::parse(payloadString);
                            }
                            payload["graphPath"] = graphManager.getImage(threadId);

                            json answer{{"sender","server"},
                                        {"topic", "provideData"},
                                        {"payload",payload}};
                            guiServer.get_con_from_hdl(guiHdl)->send(answer.dump());
                        } else if(messageJson.at("topic") == "operation"){
                            graphManager.addGraphfromCombination(messageJson.at("payload"));
                        }
                    }
                });
        // Setting Logging behavior to silent
        guiServer.clear_access_channels(websocketpp::log::alevel::all);
        guiServer.clear_error_channels(websocketpp::log::elevel::all);
        // starting the server on port 9002
        guiServer.init_asio();
        guiServer.listen(9002);
        guiServer.start_accept();
        guiServer.run();
        std::cout << "Server for GUI started" << std::endl;
    }
}

int main() {
    CAEMonitoringTool::Controller c{};
    c.startUp();
    return 0;
}


