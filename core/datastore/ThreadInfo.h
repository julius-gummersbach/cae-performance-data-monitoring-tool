#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H


#include <string>
#include <list>
#include "ThreadData.h"

using string = std::string;

class ThreadInfo {
private:
    std::list<ThreadData> data;
public:
    ThreadInfo(const long& threadId, const string name, const int& freq);
    void addData();
};


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
