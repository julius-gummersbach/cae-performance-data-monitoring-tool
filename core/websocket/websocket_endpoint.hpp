//
// Created by CAE-DUALSTUDIS on 16.01.2023.
//

#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKET_ENDPOINT_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKET_ENDPOINT_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "connection_metadata.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;
class websocket_endpoint {
public:
    websocket_endpoint();
    ~websocket_endpoint();
    int connect(std::string const &uri);
    connection_metadata::ptr get_metadata(int id) const;
    void close(int id, websocketpp::close::status::value code, std::string reason);

private:
    typedef std::map<int, connection_metadata::ptr> con_list;
    client m_endpoint;
    std::shared_ptr<std::thread> m_thread;
    con_list m_connection_list;
    int m_next_id;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKET_ENDPOINT_HPP
