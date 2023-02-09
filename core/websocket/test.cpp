
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "WebsocketEndpoint.hpp"

int main() {
    CAEMonitoringTool::Websocket::WebsocketEndpoint endpoint;
    int id = endpoint.connect("ws://localhost:5000");
    if (id != -1) {
        std::cout << "> Created connection with id " << id << std::endl;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //endpoint.send(id, "HIHIHI");

    while(true) {
        std::cout << endpoint.getMessage(id) << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    endpoint.close(id,websocketpp::close::status::going_away, "");
    return 0;
}