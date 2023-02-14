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

  /**
   * class Datamanager to store all information on incoming threads and their modules
   */
  class DataManager {

    /**
     * attribute m_threadInfos that maps all information of the threads and their Modules to their id
     */
    unordered_map<string, ThreadInfo> m_threadsInfos;

  public:

    /**
     * method to add a new thread to the map
     * @param object json representation of all the data in a thread as well as their modules
     * @return boolean value weather the given data is valid and got stored in the map
     */
    bool addData(const json &object);

    /**
     * method to get all keys in the map
     * @return list of strings containing every key in the map
     */
    std::vector<std::string> getThreadIds() const;

    /**
     * method to get a specific thread object from the map
     * @param id id of the specific thread
     * @return json representation of thread with the given id
     */
    std::string getThreadInfo(const std::string &id) const;
  };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP