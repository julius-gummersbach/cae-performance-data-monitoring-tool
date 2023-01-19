#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H

#include <string>
#include "../dataprocessing/DataTypes.hpp"

using std::string;

namespace CAEMonitoringTool::DataStore {

    /**
     * Holds Data about a few iterations of a thread
     */
    struct ThreadData {
        /* name of the thread */
        string m_name;
        /* whether this datapoint is valid */
        bool m_isValid;
        /* combined runtime of the iterations */
        double m_sumRt;
        /* maximum runtime of the iterations */
        double m_maxRt;
        /* average runtime of the iterations */
        double m_avgRt;
        /* todo */
        double m_sumVs;
        /* todo */
        double m_sumIs;

        ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs, double sumIs);
    };

}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
