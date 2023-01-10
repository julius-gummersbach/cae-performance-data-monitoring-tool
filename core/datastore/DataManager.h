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
using std::pair;

class DataManager {
public:
    void addThreadInfo(json threadInfo);

    [[nodiscard]] static const pair<bool, ThreadInfo>& getDataFromId(long id) ;

    const pair<bool,ThreadInfo>& operator[](long id) const;

private:
    map<long, ThreadInfo> m_threadInfos;

    static void addThreadData(ThreadInfo &info, const json &j) ;

    [[nodiscard]] static ThreadInfo getInfo(const json &object) ;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_H
