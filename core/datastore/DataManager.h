#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataManager {
public:
    void addThreadInfo(json threadInfo);
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H