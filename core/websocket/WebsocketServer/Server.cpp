//
// Created by CAE-DUALSTUDIS on 02.02.2023.
//
#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <string>

typedef websocketpp::server<websocketpp::config::asio> server;

server toolServer;

void on_message(websocketpp::connection_hdl h, const server::message_ptr& msg) {
    std::cout << msg->get_payload() << std::endl;
    std::string s = "test hello 123 123";
    toolServer.get_con_from_hdl(h)->send(s);
    //a:
}

int main() {
    toolServer.set_message_handler(&on_message);
    toolServer.init_asio();
    toolServer.listen(9002);
    toolServer.start_accept();
    toolServer.run();
}