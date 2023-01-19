
#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTIONMETADATA_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTIONMETADATA_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

class ConnectionMetadata{
public:
    typedef websocketpp::lib::shared_ptr<ConnectionMetadata> ptr;

    ConnectionMetadata(int id, websocketpp::connection_hdl hdl, std::string uri);
    void onOpen(client *c,websocketpp::connection_hdl hdl);
    void onFail(client *c, websocketpp::connection_hdl hdl);
    void onClose(client * c, websocketpp::connection_hdl hdl);
    void onMessage(const websocketpp::connection_hdl& hdl, const client::message_ptr& msg);
    websocketpp::connection_hdl getHdl();
    std::string getStatus();
    int getId() const;
    friend std::ostream &operator<<(std::ostream &out, ConnectionMetadata const &data);

private:
    int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::vector<std::string> m_messages;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTIONMETADATA_HPP