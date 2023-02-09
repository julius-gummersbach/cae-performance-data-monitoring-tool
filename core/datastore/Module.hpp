#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP

#include <string>
#include <memory>
#include <cmath>

namespace CAEMonitoringTool::DataStore {

  struct Module {

    /* name of the module */
    std::string m_name;

    /* sum of the realtime*/
    double m_sum_rt;

    /* max realtime*/
    double m_max_rt;

    /* average realtime */
    double m_avg_rt;

    /* sum voluntary context switches */
    double m_sum_vs;

    /* sum involuntary context switches */
    double m_sum_is;

    Module(std::string name, double sum_rt, double max_rt, double avg_rt, double sum_vs, double sum_is);

    Module();

    static std::pair<bool, Module> make(const std::string& name, double sum_rt, double max_rt,
                                         double avg_rt, double sum_vs, double sum_is);
  };
}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP