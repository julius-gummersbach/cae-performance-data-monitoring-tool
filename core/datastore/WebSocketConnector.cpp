#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * This Class is responsible for handling data received from the WebSocket.
 * It parses received data and hands it over to the DataManager
 */
class WebSocketConnector {

public:
    WebSocketConnector(const DataManager &dataManager){


    }
    /**
     * Is triggered when new data is received from the WebSocket
     * Parses the received data to a dictionary and hands it over to the DataManager
     *
     * @param json the data received as a String
     */
    void receiveData(String json){

    }
};