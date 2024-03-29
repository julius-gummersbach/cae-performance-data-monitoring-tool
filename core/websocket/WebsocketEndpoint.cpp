
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "WebsocketEndpoint.hpp"
#include "ConnectionMetadata.hpp"
#include "queue"

namespace CAEMonitoringTool::Websocket {

    typedef websocketpp::client<websocketpp::config::asio_client> client;

    WebsocketEndpoint::WebsocketEndpoint() : m_nextId(0) {
        m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
        m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

        m_endpoint.init_asio();
        m_endpoint.start_perpetual();

        m_thread.reset(new std::thread(&client::run, &m_endpoint));
    }

    WebsocketEndpoint::~WebsocketEndpoint() {
        m_endpoint.stop_perpetual();

        for (auto it = m_connection_list.begin();
             it != m_connection_list.end(); ++it) {
            if (it->second->getStatus() != "Open") {
                // Only close open connections
                continue;
            }
            std::cout << "> Closing connection " << it->second->getId() << std::endl;
            websocketpp::lib::error_code ec;
            m_endpoint.close(it->second->getHdl(), websocketpp::close::status::going_away, "", ec);
            if (ec) {
                std::cout << "> Error closing connection " << it->second->getId() << ": "
                          << ec.message() << std::endl;
            }
        }
        m_thread->join();
    }


    int WebsocketEndpoint::connect(std::string const &uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_endpoint.get_connection(uri, ec);
        if (ec) {
            std::cout << "> Connect initialization error: " << ec.message() << std::endl;
            return -1;
        }
        int newId = m_nextId++;
        ConnectionMetadata::ptr metadataPtr(new ConnectionMetadata(newId, con->get_handle(), uri));
        m_connection_list[newId] = metadataPtr;
        con->set_open_handler(std::bind(
                &ConnectionMetadata::onOpen,
                metadataPtr,
                &m_endpoint,
                websocketpp::lib::placeholders::_1
        ));
        con->set_fail_handler(std::bind(
                &ConnectionMetadata::onFail,
                metadataPtr,
                &m_endpoint,
                websocketpp::lib::placeholders::_1
        ));
        con->set_close_handler(std::bind(
                &ConnectionMetadata::onClose,
                metadataPtr,
                &m_endpoint,
                websocketpp::lib::placeholders::_1
        ));
        con->set_message_handler(std::bind(
                &ConnectionMetadata::onMessage,
                metadataPtr,
                websocketpp::lib::placeholders::_1,
                websocketpp::lib::placeholders::_2
        ));

        m_endpoint.connect(con);
        return newId;
    }

    ConnectionMetadata::ptr WebsocketEndpoint::getMetadata(int id) const {
        auto metadataIt = m_connection_list.find(id);
        if (metadataIt == m_connection_list.end()) {
            return ConnectionMetadata::ptr();
        } else {
            return metadataIt->second;
        }
    }

    void WebsocketEndpoint::send(int id, const std::string& message) {
        websocketpp::lib::error_code ec;
        auto metadataIt = m_connection_list.find(id);
        if (metadataIt == m_connection_list.end()) {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }
        m_endpoint.send(metadataIt->second->getHdl(), message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "> Error sending message: " << ec.message() << std::endl;
            return;
        }
        std::cout << "message send " << message << std::endl;
    }


    void WebsocketEndpoint::close(int id, websocketpp::close::status::value code, const std::string &reason) {
        websocketpp::lib::error_code ec;
        auto metadataIt = m_connection_list.find(id);
        if (metadataIt == m_connection_list.end()) {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }
        m_endpoint.close(metadataIt->second->getHdl(), code, reason, ec);
        if (ec) {
            std::cout << "> Error initiating close: " << ec.message() << std::endl;
        }
    }

    std::string WebsocketEndpoint::getMessage(int id) const{
        std::lock_guard<std::mutex> lk(this->getMetadata(id)->m_messageMutex);
        std::deque<std::string>& queue = this->getMetadata(id)->getMessageQueue();
        if(queue.empty()) return "";
        std::string message = queue.front();
        queue.pop_front();
        return message;
    }
}



