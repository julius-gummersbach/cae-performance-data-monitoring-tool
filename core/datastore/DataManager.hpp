#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP

#include <nlohmann/json.hpp>

namespace CAEMonitoringTool::DataStore {

        using json = nlohmann::json;

        class DataManager {
        public:
            void addThreadInfo(const json& threadInfo);
        };

    }


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
