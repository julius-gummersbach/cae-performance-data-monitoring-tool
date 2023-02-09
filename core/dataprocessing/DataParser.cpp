#include "DataParser.hpp"

namespace CAEMonitoringTool::DataProcessing {

  bool DataParser::parseThreadInfo(const json &object,
                              DataStore::DataManager &dManager,
                              GraphManager &gManager) {

    std::string id{object.at("tid")};
    std::string points;
    points.append(R"({ "tid": ")")
            .append(id)
            .append(R"(", "graph" :)")
            .append(object["graph"].dump())
            .append("}");

    gManager.addGraphFromPoints(json::parse(points));

    std::string jsonString{object.dump()};
    std::string threadInfo = jsonString.substr(0,jsonString.find("graph")-2)
            .append(jsonString.substr(jsonString.find("iterations")-2));

    dManager.addData(json::parse(jsonString));

    return object["isDone"];
  }

}