#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP

#include "nlohmann/json.hpp"
#include "ThreadInfo.hpp"
#include "../dataprocessing/DataTypes.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iostream>

using json = nlohmann::json;
using std::string;
using std::unordered_map;
using std::vector;
using std::cout;
using std::endl;
using std::pair;

namespace CAEMonitoringTool::DataStore {

/**
 * class to store all the ThreadInfos in a map sorted by their id given to it via a json object containing
 * the information from the websocket connector
 */
  class DataManager {

  public:

    /**
     * method to get new incoming date from a json library and store it in the map for later use
     *
     * @param threadInfo the json library coming from the websocket connector with the ThreadInfo objects
     */
    void addThreadInfo(const json &threadInfo);

  private:

    /**
     * map to assign a ThreadInfo object to a long value to store the data from the websocket connector
     */
    unordered_map<string, ThreadInfo> m_threadInfos;

    /**
     * method to get the ThreadData parameters from a json and add it to the given ThreadInfo
     * @param info ThreadInfo object to add the additional data to
     * @param object json representation of the data of the ThreadData object
     */
    static void addThreadData(ThreadInfo &info, const json &object);

    /**
     * method to retrieve data from the json representation of a ThreadInfo object
     * @param object json representation of the ThreadInfo
     * @return ThreadInfo object with the given data from the json library
     */
    [[nodiscard]] static ThreadInfo getInfo(const json &object);
  };

}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
