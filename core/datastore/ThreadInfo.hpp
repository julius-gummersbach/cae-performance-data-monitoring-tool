#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H

#include <string>
#include <memory>
#include <chrono>
#include <vector>
#include "ThreadData.hpp"
#include "../dataprocessing/DataTypes.hpp"

using std::string;
using Graph::time_point;

namespace CAEMonitoringTool::DataStore {

    /**
     * This class stores information of a specific thread
     */
    class ThreadInfo {
    private:
        /* unique identifier id of the Thread */
        const string m_threadId;
        /* name of the thread */
        const string m_name;
        /* starting time of the thread */
        const time_point m_startTime;
        /* frequency of the thread */
        const double m_freq;
        /* iterations that are combined in each ThreadData object associated with this thread */
        const int m_iterations;
        /* overruns the thread has gone through */
        int m_overruns;
        /* total runtime of the thread */
        double m_sumRt;
        /* ThreadData objects associated with this thread */
        std::vector<std::shared_ptr<ThreadData>> m_data;

    public:
        /* getters for the class attributes */
        [[nodiscard]] const string &getThreadId() const;
        [[nodiscard]] const string &getName() const;
        [[nodiscard]] const time_point &getStartTime() const;
        [[nodiscard]] double getFreq() const;
        [[nodiscard]] int getIterations() const;
        [[nodiscard]] int getOverruns() const;
        [[nodiscard]] double getSumRt() const;
        [[nodiscard]] const std::vector<std::shared_ptr<ThreadData>> &getData() const;

        ThreadInfo(string threadId, string name, time_point startTime, double freq, int iterations, int overruns,
                   double sumRt);

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
        void addData(const string &name,
                     double sumRt,
                     double maxRt,
                     double avgRt,
                     double sumVs,
                     double sumIs);

        /**
         * increases the overruns counter by the given delta
         *
         * @param delta
         */
        void increaseOverruns(int delta);
    };

}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
