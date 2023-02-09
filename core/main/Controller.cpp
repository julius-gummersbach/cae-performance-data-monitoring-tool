//
// Created by CAE-DUALSTUDIS on 03.02.2023.
//
#include "Controller.hpp"

#include <utility>
#include "string"
#include "thread"
#include "chrono"
#include "vector"
#include "sstream"
#include "map"

using std::string;
using std::stringstream;
using json = nlohmann::json;

class DataParser {
public:
    bool parseThreadInfo() { return true; };
};

class DataManager {
public:
    std::vector<string> getThreadIds() {
        std::vector<string> v{"a", "b", "c"};
        return v;
    };
    string getThreadInfoJson(string id){
        return "thread info, this should be a json";
    }
};

struct Graph {
    string getImage() { return "img/ExamplePlot4.svg"; }
};

class GraphManager {
public:
    std::unordered_map<string, Graph> graphs{};
};


namespace CAEMonitoringTool {
    typedef websocketpp::server<websocketpp::config::asio> server;

    void Controller::startUp() {
        DataParser m_dataParser;
        DataManager m_dataManager;
        GraphManager m_graphManager;

        // Configures the (client) endpoint and sets up a connection between it and the data Server
        CAEMonitoringTool::Websocket::WebsocketEndpoint endpoint;
        int dataConId = endpoint.connect("ws://localhost:5000");
        // Sends a message to the dataServer to let it know to start sending its data (JSON-Strings)
        endpoint.send(dataConId, "startData");
        bool isDone{true}; //TODO false
        while (!isDone) {
            // Checks the message content. If it is not empty, it parses the string into a JSON object.
            // The return value of parseThreadInfo is a boolean determined by a JSON field of the string.
            // If it equals true, that means that this was the last message to be received and the loop can be stopped.
            string mes = endpoint.getMessage(dataConId);
            if (!mes.empty()) {
                isDone = m_dataParser.parseThreadInfo();
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
                [&guiHdl, &guiServer, &m_dataManager](websocketpp::connection_hdl hdl) -> void {
                    guiHdl = std::move(hdl);
                    std::cout << "Gui connection established!" << std::endl;
                    // Get initial Threads to gui
                    auto guiConnection = guiServer.get_con_from_hdl(guiHdl);
                    for (const auto &s: m_dataManager.getThreadIds()) {
                        guiConnection->send("ST" + s);
                    }
                });
        // This method gets called for both incoming and outgoing messages
        guiServer.set_message_handler(
                [&guiServer, &guiHdl, &m_graphManager, &m_dataManager]
                        (websocketpp::connection_hdl h, const server::message_ptr &msg) -> void {
                    json messageJson = json::parse(msg->get_payload());

                    if(messageJson.at("sender") == "gui"){
                        json answer{{"sender","server"},{"payload",{{"imagePath",""},{"moduleInfo",""}}}};
                        json payload = messageJson.at("payload");
                        if(payload.at("rhs").empty()){
                            string requestedId = payload.at("lhs");
                            m_graphManager.graphs.insert({requestedId, Graph()});

                            string requestedImagePath = m_graphManager.graphs[requestedId].getImage();
                            std::cout << requestedImagePath << std::endl;
                            string requestedJsonContent = m_dataManager.getThreadInfoJson(requestedId);
                            answer.at("imagePath") = requestedImagePath;
                            std::cout << answer << std::endl;
                        } else {

                        }
                        guiServer.get_con_from_hdl(guiHdl)->send(answer);
                    } else {

                    }
                    /*
                    string messageContent = msg->get_payload();
                    std::cout << "Message received: " << messageContent << std::endl;
                    // -----Message deciphering-----
                    // Origin: "S" if the message comes from the Server, "G" if it comes from the GUI
                    string messageOrigin = messageContent.substr(0, 1);
                    std::cout << messageOrigin << std::endl;
                    // Use cases:
                    // 1) Send thread id, operator and second thread id -> receive Image path, content for "Thread" and "Modules" table
                    // 2) Send thread id -> receive Image path, content for "Thread" and "Modules" table
                    if (messageOrigin == "G") {
                        string answer{"S"};
                        // find out if just an id, or 2 ids with an operation were sent -> second char either "1" or "2"
                        string requestType = messageContent.substr(1, 1);
                        if (requestType == "1") {
                            string requestedId = messageContent.substr(2);

                            m_graphManager.graphs.insert({requestedId, Graph()});

                            string requestedImagePath = m_graphManager.graphs[requestedId].getImage();
                            std::cout << requestedImagePath << std::endl;
                            string requestedJsonContent = m_dataManager.getThreadInfoJson(requestedId);
                            answer += (requestedImagePath + "|" + requestedJsonContent);
                            std::cout << answer << std::endl;
                        } else {
                            // Parse the two ids and operator
                        }

                    }*/
                });
        // Setting Logging behavior to silent
        guiServer.clear_access_channels(websocketpp::log::alevel::all);
        guiServer.clear_error_channels(websocketpp::log::elevel::all);
        // starting the server on port 9002
        guiServer.init_asio();
        guiServer.listen(9002);
        guiServer.start_accept();
        guiServer.run();
    }
}

int main() {
    CAEMonitoringTool::Controller c;
    c.startUp();
    return 0;
}


