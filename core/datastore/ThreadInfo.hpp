#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_HPP


#include <string>
#include <list>
#include "ThreadData.hpp"

using std::string;

/**
 * This class stores information of a specific thread
 */
class ThreadInfo {
private:
    string m_threadId;
    string m_name;
    double m_freq;
    int m_iterations;
    int m_overruns;
    double m_sumRt;
    std::list<ThreadData> m_data;
public:
    ThreadInfo(string threadId, string name, double freq);

    void addData(const string& name,
                 double sumRt,
                 double maxRt,
                 double avgRt,
                 double sumVs,
                 double sumIs);

    [[nodiscard]] string getThreadId() const;

    [[nodiscard]] string getName() const;
};

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_HPP
