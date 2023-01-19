
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
//#include <websocketpp/common/thread.hpp>
//#include <websocketpp/common/memory.hpp>
//#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <vector>
#include "ConnectionMetadata.hpp"
#include "WebsocketEndpoint.hpp"


int main() {
    bool done = false;
    std::string input;
    WebsocketEndpoint endpoint;
    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);
        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                    << "\nCommand List:\n"
                    << "connect <ws uri>\n"
                    << "close <connection id> [<close code:default=1000>] [<close reason>]\n"
                    << "help: Display this help text\n"
                    << "quit: Exit the program\n"
                    << std::endl;
        }  else if (input.substr(0,7) == "connect") {
            int id = endpoint.connect(input.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input.substr(0,5) == "close") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            int closeCode = websocketpp::close::status::normal;
            std::string reason;

            ss >> cmd >> id >> closeCode;
            std::getline(ss,reason);

            endpoint.close(id, closeCode, reason);
        } else {
            std::cout << "Unrecognized Command" << std::endl;
        }
    }
}
