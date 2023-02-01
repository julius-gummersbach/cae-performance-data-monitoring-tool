#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP

#include "nlohmann/json.hpp"
#include "../datastore/DataManager.hpp"
#include "GraphManager.hpp"
#include "string"

namespace CAEMonitoringTool::DataProcessing {

  class DataParser {

    using json = nlohmann::json;

  public:
    static bool parseThreadInfo(const json &object,
                                DataStore::DataManager &dManager,
                                GraphManager &gManager);
  };
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP