
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "ConnectionMetadata.hpp"
//#include "../datastore/DataManager.hpp"
#include <nlohmann/json.hpp>
#include <utility>
#include "mutex"

namespace CAEMonitoringTool::Websocket {

    typedef websocketpp::client<websocketpp::config::asio_client> client;

    typedef websocketpp::lib::shared_ptr<ConnectionMetadata> ptr;

    ConnectionMetadata::ConnectionMetadata(int id, websocketpp::connection_hdl hdl, std::string uri)
            : m_id(id), m_hdl(std::move(std::move(hdl))), m_status("Connecting"), m_uri(std::move(uri)),
              m_server("N/A") {}

    void ConnectionMetadata::onOpen(client *c, websocketpp::connection_hdl hdl) {
        m_status = "Open";
        client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
        m_server = con->get_response_header("Server");
    }

    void ConnectionMetadata::onFail(client *c, websocketpp::connection_hdl hdl) {
        m_status = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
        m_server = con->get_response_header("Server");
        m_error_reason = con->get_ec().message();
    }

    void ConnectionMetadata::onClose(client *c, websocketpp::connection_hdl hdl) {
        m_status = "Closed";
        client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " ("
          << websocketpp::close::status::get_string(con->get_remote_close_code())
          << "), close reason: " << con->get_remote_close_reason();
        m_error_reason = s.str();
    }

    void ConnectionMetadata::onMessage(const websocketpp::connection_hdl &hdl, const client::message_ptr &msg) {
        std::lock_guard<std::mutex> lk(m_messageMutex);
        m_messages.push_back(msg->get_payload());
    }

    websocketpp::connection_hdl ConnectionMetadata::getHdl() { return m_hdl; }

    std::string ConnectionMetadata::getStatus() { return m_status; }

    int ConnectionMetadata::getId() const { return m_id; }

    std::deque<std::string>& ConnectionMetadata::getMessageQueue() {
        return m_messages;
    }
}