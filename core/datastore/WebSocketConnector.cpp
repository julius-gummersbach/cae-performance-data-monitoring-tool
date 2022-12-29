#include <nlohmann/json.hpp>
#include <algorithm>
#include <string>
#include "DataManager.cpp"
#include "WebSocketConnector.h"

using json = nlohmann::json;

WebSocketConnector::WebSocketConnector(const DataManager &dataManager) : m_dataManager{std::move(dataManager)}{
}

void WebSocketConnector::receiveData(std::string jsonString) {
    m_dataManager.addThreadInfo(json::parse(jsonString))
}