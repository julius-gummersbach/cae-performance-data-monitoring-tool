#include "DataParser.hpp"

namespace CAEMonitoringTool::DataProcessing {

  bool DataParser::parseThreadInfo(const json &object,
                              DataStore::DataManager &dManager,
                              GraphManager &gManager) {
    std::string dataInfo;
    std::string graphInfo;

    std::string jsonString{object.dump()};



    return true;
  }

}