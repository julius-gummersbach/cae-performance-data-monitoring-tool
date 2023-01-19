
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include <iostream>
#include <thread>
#include "WebsocketEndpoint.hpp"

int main() {
    bool done = false;
    std::string input;
    CAEMonitoringTool::Websocket::WebsocketEndpoint endpoint;
    int id = endpoint.connect("ws://localhost:5000");
    if (id != -1) {
        std::cout << "> Created connection with id " << id << std::endl;
    }
    endpoint.send(id, "HIHIHI");
    //endpoint.close(0,websocketpp::close::status::going_away, "");
    return 0;
}