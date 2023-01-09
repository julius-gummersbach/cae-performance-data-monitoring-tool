#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETCONNECTOR_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETCONNECTOR_H

#include <nlohmann/json.hpp>
#include <algorithm>
#include "DataManager.h"

using json = nlohmann::json;

/**
 * This class is responsible for handling m_data received from the websocket.
 * It parses received m_data and hands it over to the DataManager
 */
class WebSocketConnector {
private:
    DataManager m_dataManager;

public:
    explicit WebSocketConnector(const DataManager &dataManager);

    /**
     * Is triggered when new m_data is received from the websocket
     * Parses the received m_data to a dictionary and hands it over to the DataManager
     *
     * @param jsonString the m_data received as a String
     */
    void receiveData(const std::string &jsonString);
};
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_WEBSOCKETCONNECTOR_H
