#include <nlohmann/json.hpp>
#include <algorithm>
#include <string>
#include "DataManager.cpp"

using json = nlohmann::json;

/**
 * This Class is responsible for handling data received from the WebSocket.
 * It parses received data and hands it over to the DataManager
 */
class WebSocketConnector {
private:
    DataManager dataManager;

public:
    explicit WebSocketConnector(const DataManager &dataManager) : dataManager(std::move(dataManager)){

    }

    /**
     * Is triggered when new data is received from the WebSocket
     * Parses the received data to a dictionary and hands it over to the DataManager
     *
     * @param jsonString the data received as a String
     */
    void receiveData(std::string jsonString) {
        dataManager.addThreadInfo(json::parse(jsonString))
    }
};