#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP

#include <string>
#include <memory>
#include <cmath>

namespace CAEMonitoringTool::DataStore {

  /**
   * struct to store all information of the modules of a thread
   */
  struct Module {

    /**
     * name of the module
     */
    std::string m_name;

    /**
     * sum of the realtime
     */
    double m_sum_rt;

    /**
     * max realtime
     */
    double m_max_rt;

    /**
     * average realtime
     */
    double m_avg_rt;

    /**
     * sum voluntary context switches
     */
    double m_sum_vs;

    /**
     * sum involuntary context switches
     */
    double m_sum_is;

    /**
     * factory method of the struct method to create a new module
     * @param name
     * @param sum_rt
     * @param max_rt
     * @param avg_rt
     * @param sum_vs
     * @param sum_is
     * @return pair of a boolean whether the data is valid and the corresponding module object in case they were
     */
    static std::pair<bool, Module> make(const std::string& name, double sum_rt, double max_rt,
                                         double avg_rt, double sum_vs, double sum_is);

  private:
    /**
     * constructor of the module struct, setting all attributes
     * @param name
     * @param sum_rt
     * @param max_rt
     * @param avg_rt
     * @param sum_vs
     * @param sum_is
     */
    Module(std::string name, double sum_rt, double max_rt, double avg_rt, double sum_vs, double sum_is);

    /**
     * dummy default constructor of the module struct
     */
    Module();

  };
}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_MODULE_HPP