#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP

#include "nlohmann/json.hpp"
#include "ThreadInfo.hpp"
#include "../dataprocessing/DataTypes.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <deque>

namespace CAEMonitoringTool::DataStore {

  using json = nlohmann::json;
  using std::string;
  using std::unordered_map;
  using std::vector;
  using std::cout;
  using std::endl;
  using std::pair;

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
       * general function pointer for the getter functions for the attributes of the threaddata objects
       */
      typedef const double &(*getterFunc)(const ThreadData &data);

      /**
       * map to assign a ThreadInfo object to a long value to store the data from the websocket connector
       */
      unordered_map<string, ThreadInfo> m_threadInfos;

      /**
       * method to retrieve data from the json representation of a ThreadInfo object
       * @param object json representation of the ThreadInfo
       * @return ThreadInfo object with the given data from the json library
       */
      [[nodiscard]] static ThreadInfo getInfo(const json &object);

      /**
       * method to calculate all the threaddata objects in the given time intervall and return the requestes data type
       * from those using the passed function
       *
       * @param info threadinfo object the data the data has to be retrieved from
       * @param data list of threaddata objects the attributes have to be retrieves from
       * @param startTime start time point of the time interval
       * @param length length of the time interval in nanoseconds
       * @param func pointer to the getter function to get the right attribute form the thread data objects
       * @return a list of points with the values of the given type in the given time interval
       */
      static std::deque<double> getData(const ThreadInfo &info,
                                        const std::vector<std::shared_ptr<ThreadData>> &data,
                                        const DataProcessing::time_point &startTime,
                                        const DataProcessing::time_delta &length,
                                        const getterFunc &func);

    /**
     * method to get the ThreadData parameters from a json and add it to the given ThreadInfo
     * @param info ThreadInfo object to add the additional data to
     * @param j json representation of the data of the ThreadData object
     */
    static void addThreadData(ThreadInfo &info, const json &j);
  };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP