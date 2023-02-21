#include "DataParser.hpp"


namespace CAEMonitoringTool::DataProcessing {

  bool DataParser::parseThreadInfo(const std::string &jsonContent,
                                   DataStore::DataManager &dManager,
                                   GraphManager &gManager) {

    json graph, data;
    json object = json::parse(jsonContent);

    for(auto itr = object.begin(); itr != object.end() ;++itr) {
      if(itr.key() == "tid") {
        graph["tid"] = itr.value();
        data["tid"] = itr.value();
      } else if (itr.key() == "isDone") {
        continue;
      } else if (itr.key() == "graph") {
          graph["graph"] = itr.value();
      } else {
        data[itr.key()] = itr.value();
      }
    }

    dManager.addData(data);
    gManager.addGraphFromPoints(graph);

    return object["isDone"];
  }

}