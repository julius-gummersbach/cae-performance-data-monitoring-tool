#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H


#include <string>

using MonitoringTool::DataProcessing::time_point;
using std::string;

namespace MonitoringTool::DataStore {

    struct ThreadData {
        string m_name;
        bool m_isValid;
        /* combined runtime of the iterations */
        double m_sumRt;
        double m_maxRt;
        double m_avgRt;
        double m_sumVs;
        double m_sumIs;

        ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs,
                   double sumIs);
    };

}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
