//
// Created by CAE-DUALSTUDIS on 16.01.2023.
//
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocket_endpoint.hpp"
#include "connection_metadata.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

websocket_endpoint::websocket_endpoint() : m_next_id(0) {
    m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
    m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

    m_endpoint.init_asio();
    m_endpoint.start_perpetual();

    m_thread.reset(new std::thread(&client::run, &m_endpoint));
}

websocket_endpoint::~websocket_endpoint() {
    m_endpoint.stop_perpetual();

    for (con_list::const_iterator it = m_connection_list.begin(); it != m_connection_list.end(); ++it) {
        if (it->second->get_status() != "Open") {
            // Only close open connections
            continue;
        }
        std::cout << "> Closing connection " << it->second->get_id() << std::endl;
        websocketpp::lib::error_code ec;
        m_endpoint.close(it->second->get_hdl(), websocketpp::close::status::going_away, "", ec);
        if (ec) {
            std::cout << "> Error closing connection " << it->second->get_id() << ": "
                      << ec.message() << std::endl;
        }
    }
    m_thread->join();
}


int websocket_endpoint::connect(std::string const &uri) {
    websocketpp::lib::error_code ec;
    client::connection_ptr con = m_endpoint.get_connection(uri, ec);
    if (ec) {
        std::cout << "> Connect initialization error: " << ec.message() << std::endl;
        return -1;
    }
    int new_id = m_next_id++;
    connection_metadata::ptr metadata_ptr(new connection_metadata(new_id, con->get_handle(), uri));
    m_connection_list[new_id] = metadata_ptr;
    con->set_open_handler(websocketpp::lib::bind(
            &connection_metadata::on_open,
            metadata_ptr,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
    ));
    con->set_fail_handler(websocketpp::lib::bind(
            &connection_metadata::on_fail,
            metadata_ptr,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
    ));
    con->set_close_handler(websocketpp::lib::bind(
            &connection_metadata::on_close,
            metadata_ptr,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
    ));
    con->set_message_handler(websocketpp::lib::bind(
            &connection_metadata::on_message,
            metadata_ptr,
            websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2
    ));

    m_endpoint.connect(con);
    return new_id;
}

connection_metadata::ptr websocket_endpoint::get_metadata(int id) const {
    con_list::const_iterator metadata_it = m_connection_list.find(id);
    if (metadata_it == m_connection_list.end()) {
        return connection_metadata::ptr();
    } else {
        return metadata_it->second;
    }
}

void websocket_endpoint::close(int id, websocketpp::close::status::value code, std::string reason) {
    websocketpp::lib::error_code ec;
    con_list::iterator metadata_it = m_connection_list.find(id);
    if (metadata_it == m_connection_list.end()) {
        std::cout << "> No connection found with id " << id << std::endl;
        return;
    }
    m_endpoint.close(metadata_it->second->get_hdl(), code, reason, ec);
    if (ec) {
        std::cout << "> Error initiating close: " << ec.message() << std::endl;
    }
}




