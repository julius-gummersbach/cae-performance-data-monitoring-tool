//
// Created by CAE-DUALSTUDIS on 16.01.2023.
//

#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTION_METADATA_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTION_METADATA_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"


typedef websocketpp::client<websocketpp::config::asio_client> client;

class connection_metadata{
public:
    typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

    connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri);
    void on_open(client *c, websocketpp::connection_hdl hdl);
    void on_fail(client *c, websocketpp::connection_hdl hdl);
    void on_close(client * c, websocketpp::connection_hdl hdl);
    void on_message(const websocketpp::connection_hdl& hdl, const client::message_ptr& msg);
    websocketpp::connection_hdl get_hdl();
    std::string get_status();
    int get_id() const;
    friend std::ostream &operator<<(std::ostream &out, connection_metadata const &data);

private:
    int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::vector<std::string> m_messages;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTION_METADATA_HPP