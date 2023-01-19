
#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTIONMETADATA_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONNECTIONMETADATA_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

/**
 *  Tracks information about connections.
 */
class ConnectionMetadata{
public:
    typedef websocketpp::lib::shared_ptr<ConnectionMetadata> ptr;

    /**
     *  This object stores the numeric connection id and a number of fields that will be filled in as the connection is processed.
     *  This includes the state of the connection (opening, open, failed, closed, etc),
     *  the original URI connected to, an identifying value from the server,
     *  and a description of the reason for connection failure/closure
     * @param id connection id
     * @param hdl connection handles used by endpoint methods to identify the target of the desired action.
     * @param uri original URI connected to
     */
    ConnectionMetadata(int id, websocketpp::connection_hdl hdl, std::string uri);
    void onOpen(client *c,websocketpp::connection_hdl hdl);
    void onFail(client *c, websocketpp::connection_hdl hdl);
    void onClose(client * c, websocketpp::connection_hdl hdl);
    void onMessage(const websocketpp::connection_hdl& hdl, const client::message_ptr& msg);
    /**
     * @return the connection handle
     */
    websocketpp::connection_hdl getHdl();
    /**
     * @return the status of the connection
     */
    std::string getStatus();
    /**
     * @return the id of the connection
     */
    [[nodiscard]] int getId() const;

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