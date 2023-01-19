
#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "ConnectionMetadata.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;


/**
 * Creates and launches new connections and maintains default settings for those connections.
 * Endpoints also manage any shared network resources.
 */
class WebsocketEndpoint {
public:
    /**
     *  Initializes the transport system.
     *  Processes connection tasks (read and deliver incoming messages, frame and send outgoing messages, etc) on an extra thread
     */
    WebsocketEndpoint();
    /**
     * Closes all connections and joins the thread on wich the WebsocketEndpoint object ran.
     */
    ~WebsocketEndpoint();
    /**
     * Creates and configures a connection request, then submits it back to the endpoint to make a new connection out of it.
     * Inside this method, handlers are registered. (For example "onOpen", "onFail", "onMessage" etc.)
     * @param uri the uri to connect to.
     * @return The id of this connection.
     */
    int connect(std::string const &uri);
    /**
     * Retrieves metadata associated with the connection with the given id.
     * @param id the id of a connection
     * @return A ConnectionMetadata object, see ConnectionMetadata.hpp for more information.
     */
    ConnectionMetadata::ptr getMetadata(int id) const;
    /**
     * Closes a connection with the given id.
     * @param id The id of the connection
     * @param code a code for the closing reason
     * @param reason the reason in human readable form.
     */
    void close(int id, websocketpp::close::status::value code, const std::string& reason);

private:
    typedef std::map<int, ConnectionMetadata::ptr> con_list;
    client m_endpoint;
    std::shared_ptr<std::thread> m_thread;
    con_list m_connection_list;
    int m_nextId;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETENDPOINT_HPP
