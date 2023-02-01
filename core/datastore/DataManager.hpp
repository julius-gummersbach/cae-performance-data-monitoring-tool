#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP

#include "nlohmann/json.hpp"
#include "ThreadInfo.hpp"
#include <unordered_map>
#include <vector>

namespace CAEMonitoringTool::DataStore {

  using json = nlohmann::json;
  using std::string;
  using std::unordered_map;

  class DataManager {

    unordered_map<string, ThreadInfo> m_threadsInfos;

  public:

    void addData(const json &object);

    std::string getModulesJSON(const std::string& id) const;

    std::vector<std::string> getThreadIds() const;
  };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP