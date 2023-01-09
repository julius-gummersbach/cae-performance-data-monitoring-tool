#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H

#include "nlohmann/json.hpp"
#include "ThreadInfo.h"
#include <iostream>
#include <map>
#include <vector>
#include <iostream>

using json = nlohmann::json;
using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H

class DataManager {
public:
    void addThreadInfo(json threadInfo);

private:
    map<long, vector<ThreadInfo>> m_threadInfos;

    void addThreadData(ThreadInfo &info, const json &j) const;

    ThreadInfo getInfo(const json &object) const;
};