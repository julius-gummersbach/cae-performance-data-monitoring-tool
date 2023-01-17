//
// Created by CAE-DUALSTUDIS on 16.01.2023.
//
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "connection_metadata.hpp"
//#include "../datastore/DataManager.hpp"
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

typedef websocketpp::client<websocketpp::config::asio_client> client;

typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

connection_metadata::connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
        : m_id(id), m_hdl(std::move(std::move(hdl))), m_status("Connecting"), m_uri(std::move(uri)), m_server("N/A") {}

void connection_metadata::on_open(client *c, websocketpp::connection_hdl hdl) {
    m_status = "Open";
    client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
    m_server = con->get_response_header("Server");
}

void connection_metadata::on_fail(client *c, websocketpp::connection_hdl hdl) {
    m_status = "Failed";

    client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
    m_server = con->get_response_header("Server");
    m_error_reason = con->get_ec().message();
}

void connection_metadata::on_close(client *c, websocketpp::connection_hdl hdl) {
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(std::move(hdl));
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
      << websocketpp::close::status::get_string(con->get_remote_close_code())
      << "), close reason: " << con->get_remote_close_reason();
    m_error_reason = s.str();
}

void connection_metadata::on_message(const websocketpp::connection_hdl& hdl, const client::message_ptr& msg) {
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {

        json j = json::parse(msg->get_payload());
        //DataManager::addThreadInfo(j);
        m_messages.push_back(msg->get_payload());
    } else {
        m_messages.push_back(websocketpp::utility::to_hex(msg->get_payload()));
    }
}

websocketpp::connection_hdl connection_metadata::get_hdl() { return m_hdl; }

std::string connection_metadata::get_status() { return m_status; }

int connection_metadata::get_id() const { return m_id; }





