#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H

#include <string>
#include <list>
#include "ThreadData.h"

using std::string;

/**
 * This class stores information of a specific thread
 */
class ThreadInfo {
private:
    /* unique identifier id of the Thread */
    long m_threadId;
    /* name of the thread */
    string m_name;
    /* frequency of the thread */
    double m_freq;
    /* iterations the thread has gone through */
    int m_iterations;
    /* overruns the thread has gone through */
    int m_overruns;
    /* total runtime of the thread */
    double m_sumRt;
    /* ThreadData objects associated with this thread */
    std::list<ThreadData> m_data;
public:
    ThreadInfo(long threadId, string name, double freq);

    /**
     * adds a new ThreadData object to the m_data list
     *
     * @param name attribute of the to be created ThreadData object
     * @param sumRt attribute of the to be created ThreadData object
     * @param maxRt attribute of the to be created ThreadData object
     * @param avgRt attribute of the to be created ThreadData object
     * @param sumVs attribute of the to be created ThreadData object
     * @param sumIs attribute of the to be created ThreadData object
     */
    void addData(const string& name,
                 double sumRt,
                 double maxRt,
                 double avgRt,
                 double sumVs,
                 double sumIs);
};


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H