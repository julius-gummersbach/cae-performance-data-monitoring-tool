
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

std::ostream &operator<<(std::ostream &out, ConnectionMetadata const &data) {
    out << "> URI: " << data.m_uri << "\n"
        << "> Status: " << data.m_status << "\n"
        << "> Remote Server: " << (data.m_server.empty() ? "None Specified" : data.m_server) << "\n"
        << "> Error/close reason: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason) << "\n"
        << "> Messages Processed: (" << data.m_messages.size() << ") \n";
    std::vector<std::string>::const_iterator it;
    for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it) {
        out << *it << "\n";
    }
    return out;
}

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
                    << "show <connection id>\n"
                    << "help: Display this help text\n"
                    << "quit: Exit the program\n"
                    << std::endl;
        }  else if (input.substr(0,7) == "connect") {
            int id = endpoint.connect(input.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input.substr(0,4) == "show") {
            int id = atoi(input.substr(5).c_str());

            ConnectionMetadata::ptr metadata = endpoint.getMetadata(id);
            if (metadata) {
                std::cout << *metadata << std::endl;
            } else {
                std::cout << "> Unknown connection id " << id << std::endl;
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
