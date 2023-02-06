//
// Created by CAE-DUALSTUDIS on 03.02.2023.
//

#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONTROLLER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONTROLLER_HPP

#include "../websocket/WebsocketEndpoint.hpp"
#include "../datastore/DataManager.hpp"
#include "../dataprocessing/GraphManager.hpp"
#include "websocketpp/server.hpp"
#include <websocketpp/config/asio_no_tls.hpp>
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"

namespace CAEMonitoringTool {
    class Controller {
        DataStore::DataManager m_dataManager;
        //DataProcessing::GraphManager m_graphManager;
    public:
        void startUp();

    };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_CONTROLLER_HPP
