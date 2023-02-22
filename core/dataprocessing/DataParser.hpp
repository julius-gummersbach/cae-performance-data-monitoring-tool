#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP

#include <nlohmann/json.hpp>
#include "../datastore/DataManager.hpp"
#include "GraphManager.hpp"
#include "string"
#include "queue"
#include "thread"

namespace CAEMonitoringTool::DataProcessing {

  using json = nlohmann::json;

  /**
   * class to receive the incoming json-data strings from the websocket-connector, parse and redistribute it
   * to the DataManager and GraphManager
   */
  class DataParser {

    std::thread m_dataThread;
    std::thread m_graphThread;
    std::thread m_parseThread;

    std::queue<json*> m_dataToAdd;
    std::queue<json*> m_graphsToAdd;
    std::queue<json*> m_dataToPrepare;

    bool m_gotLastMessage;

    std::mutex m_mMutex;

  public:

    /**
     * method to take the incoming data from the websocket as a json string representation, parse it and distribute it
     * to the data-manager and graph-manager
     * @param object string representation of a json object of all information of a single thread
     * @return boolean if this was the last sent object from the websocket
     */
    bool parseThreadInfo(const std::string &jsonContent);

    void init(DataStore::DataManager &dManager, GraphManager &gManager, DataParser &dataParser);

    static void workOnData(DataParser &parser, DataStore::DataManager &dManager);

    static void workOnGraphs(DataParser &parser, GraphManager &dManager);

    static void workOnJSON(DataParser& parser);

    void addData(DataStore::DataManager &dManager);

    void addGraph(GraphManager &gManager);

    void prepareData();
  };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP