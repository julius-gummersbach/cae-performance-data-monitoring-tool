//
// Created by CAE-DUALSTUDIS on 02.02.2023.
//
#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <string>

typedef websocketpp::server<websocketpp::config::asio> server;

server print_server;

void on_message(websocketpp::connection_hdl h, server::message_ptr msg) {
    std::cout << "TEST MARIA" << msg->get_payload() << std::endl;
    std::string s = "hii";
    print_server.get_con_from_hdl(h)->send(s);
}

int main() {
    print_server.set_message_handler(&on_message);
    print_server.init_asio();
    print_server.listen(9002);
    print_server.start_accept();
    print_server.run();
}