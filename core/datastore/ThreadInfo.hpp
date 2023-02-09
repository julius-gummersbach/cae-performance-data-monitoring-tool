#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H

#include <string>
#include <cmath>
#include <memory>
#include <vector>
#include "nlohmann/json.hpp"
#include "Module.hpp"

namespace CAEMonitoringTool::DataStore {

  using std::string;
  using json = nlohmann::json;

  /**
   * This class stores information of a specific thread
   */
  struct ThreadInfo {
    /* the thread id */
    const string m_threadId;
    /* the thread name */
    const string m_name;
    /* the thread frequency */
    const double m_freq;
    /* amount of iterations */
    const int m_iterations;
    /* amount of detected overruns */
    int m_overruns;
    /* sum over sumRt of the modules */
    double m_sumRt;
    /* list about all modules running in the thread */
    std::vector<std::shared_ptr<Module>> m_modules;
    /* json string representation of the info object */
    std::string m_jsonStr;

    ThreadInfo(string threadId, string name, const double &freq, const int &iterations, const int &overruns,
               const double &sumRt, string jsonStr);

    ThreadInfo();

    static std::pair<bool, ThreadInfo> make(const string& threadId, const string& name, const double &freq,
                                            const int &iterations, const int &overruns, const double &sumRt,
                                            const string& jsonStr);

    explicit operator string() const;
  };
}

#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADINFO_H