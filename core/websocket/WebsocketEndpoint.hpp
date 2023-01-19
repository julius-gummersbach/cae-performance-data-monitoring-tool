
#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "ConnectionMetadata.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

class WebsocketEndpoint {
public:
    WebsocketEndpoint();
    ~WebsocketEndpoint();
    int connect(std::string const &uri);
    ConnectionMetadata::ptr getMetadata(int id) const;
    void close(int id, websocketpp::close::status::value code, const std::string& reason);

private:
    typedef std::map<int, ConnectionMetadata::ptr> con_list;
    client m_endpoint;
    std::shared_ptr<std::thread> m_thread;
    con_list m_connection_list;
    int m_nextId;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
