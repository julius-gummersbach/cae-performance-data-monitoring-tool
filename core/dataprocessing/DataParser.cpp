#include "DataParser.hpp"


namespace CAEMonitoringTool::DataProcessing {

  bool DataParser::parseThreadInfo(const std::string &jsonContent,
                                   DataStore::DataManager &dManager,
                                   GraphManager &gManager) {

    std::string threadInfo = jsonContent.substr(0, jsonContent.find("graph") - 2)
            .append(jsonContent.substr(jsonContent.find("iterations") - 2));
    json object = json::parse(jsonContent);

    if(dManager.addData(json::parse(threadInfo))) {
      std::string id{object["tid"]};
      std::string points;
      points.append(R"({ "tid": ")")
              .append(id)
              .append(R"(", "graph" :)")
              .append(object["graph"].dump())
              .append("}");
      gManager.addGraphFromPoints(json::parse(points));
    }

    return object["isDone"];
  }

}