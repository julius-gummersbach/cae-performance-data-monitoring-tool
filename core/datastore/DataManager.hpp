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
     * overloading of the []-operator as a way to retrieve the ThreadInfo objects from the map via a given
     * id
     *
     * @param id id of the ThreadInfo object to retrieve
     * @return a boolean-ThreadInfo pair in which the first boolean value indicates if the request was
     * successful and a ThreadInfo object with the given id was found and returned or unsuccessful and a
     * dummy ThreadInfo object is created and returned with null-values as attributes
     */
    const std::pair<bool, ThreadInfo> &operator[](const string &id) const;

    /**
     * method for the graph-expressions to get the data points for the graphs from the data manager in a given time
     * interval
     *
     * @param id id of the threadinfo object the data has to be retrieved from
     * @param startTime start time point of the time interval
     * @param length length of the time interval in nanoseconds
     * @param type data type of the graph
     * @return a list of points with the values of the given type in the given time interval
     */
    std::deque<double> getPointsInIntervall(const string &id,
                                            const Graph::time_point &startTime,
                                            const Graph::time_delta &length,
                                            const Graph::GraphDataType &type) const;

  private:

    /**
     * general function pointer for the getter functions for the attributes of the threaddata objects
     */
    typedef const double&(*getterFunc)(const ThreadData &data);

    /**
     * map to assign a ThreadInfo object to a long value to store the data from the websocket connector
     */
    std::unordered_map<string, ThreadInfo> m_threadInfos;

    /**
     * method to be called by the overloaded []-operator to retrieve data from the map
     * @param id id of the data to be retrieved
     * @return boolean-ThreadInfo pair in which the first parameter indicates if the process was successful
     * and the second is the data object from the map or a dummy object
     */
    [[nodiscard]] static const std::pair<bool, ThreadInfo> &getDataFromId(const string &id);

    /**
     * method to get the ThreadData parameters from a json and add it to the given ThreadInfo
     * @param info ThreadInfo object to add the additional data to
     * @param j json representation of the data of the ThreadData object
     */
    static void addThreadData(ThreadInfo &info, const json &j);
     * @param object json representation of the data of the ThreadData object
     */
    static void addThreadData(ThreadInfo &info, const json &object);

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
                               const Graph::time_point &startTime,
                               const Graph::time_delta &length,
                               const getterFunc &func);
  };

}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAMANAGER_HPP
