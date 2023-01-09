#include "WebSocketConnector.h"

WebSocketConnector::WebSocketConnector(const DataManager &dataManager){
using json = nlohmann::json;

WebSocketConnector::WebSocketConnector(const DataManager &dataManager) :
m_dataManager{std::move(dataManager)}{
}

void WebSocketConnector::receiveData(const std::string &jsonString){
void WebSocketConnector::receiveData(std::string jsonString) {
    m_dataManager.addThreadInfo(json::parse(jsonString));
}
