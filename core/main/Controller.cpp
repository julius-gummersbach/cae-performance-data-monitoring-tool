//
// Created by CAE-DUALSTUDIS on 03.02.2023.
//
#include "Controller.hpp"
#include "string"
#include "thread"
#include "chrono"

using std::string;

class DataParser{
public:
    bool parseThreadInfo(){return true;};
};


namespace CAEMonitoringTool {
    typedef websocketpp::server<websocketpp::config::asio> server;

    /*
    void on_message(websocketpp::connection_hdl h, const server::message_ptr &msg) {
        std::cout << msg->get_payload() << std::endl;
        std::string s = "test hello 123 123";
        //Controller::m_guiServer.get_con_from_hdl(h)->send(s);
    }
     */
    void Controller::startUp() {
        server guiServer;
        //guiServer.set_message_handler(&on_message);
        guiServer.set_message_handler(
                [&guiServer](websocketpp::connection_hdl h, const server::message_ptr &msg)-> void{
                    std::cout << msg->get_payload() << std::endl;
                    std::string s = "test hello 123 123";
                    guiServer.get_con_from_hdl(h)->send(s);
        });
        guiServer.init_asio();
        guiServer.listen(9002);
        guiServer.start_accept();
        guiServer.run();

        DataParser m_dataParser;

        // Configures the (client) endpoint and sets up a connection between it and the data Server
        CAEMonitoringTool::Websocket::WebsocketEndpoint endpoint;
        int dataConId = endpoint.connect("ws://localhost:5000");
        // Sends a message to the dataServer to let it know to start sending its data (JSON-Strings)
        endpoint.send(dataConId, "startData");
        bool isDone{false};
        while (!isDone) {
            // Checks the message content. If it is not empty, it parses the string into a JSON object.
            // The return value of parseThreadInfo is a boolean determined by a JSON field of the string.
            // If it equals true, that means that this was the last message to be received and the loop can be stopped.
            string mes = endpoint.getMessage(dataConId);
            if(!mes.empty()){
                isDone = m_dataParser.parseThreadInfo();
            } else {
                // If the message content is empty, that means the next message has not been received yet,
                // and we need to wait for that.
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }
}

int main() {
    CAEMonitoringTool::Controller c;
    c.startUp();
    return 0;
}


