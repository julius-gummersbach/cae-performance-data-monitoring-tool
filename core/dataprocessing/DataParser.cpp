#include "DataParser.hpp"


namespace CAEMonitoringTool::DataProcessing {

  bool DataParser::parseThreadInfo(const std::string &jsonContent) {
    json object = json::parse(jsonContent);
    m_dataToPrepare.push(&object);
    bool isDone = object["isDone"];
    if (isDone) {
      m_parseThread.join();
      m_dataThread.join();
      m_graphThread.join();
    }
    return isDone;
  }

  void DataParser::init(DataStore::DataManager &dManager, GraphManager &gManager, DataParser &dataParser) {
    dataParser.m_gotLastMessage = false;

    m_parseThread = std::thread(workOnJSON, std::ref(dataParser));
    m_dataThread = std::thread(workOnData, std::ref(dataParser), std::ref(dManager));
    m_graphThread = std::thread(workOnGraphs, std::ref(dataParser), std::ref(gManager));
  }

  void DataParser::workOnJSON(DataParser &parser) {
    while (!(parser.m_gotLastMessage && parser.m_dataToPrepare.empty())) {
      if (!parser.m_dataToPrepare.empty()) {
        parser.prepareData();
      }
    }
  }

  void DataParser::prepareData() {
    json *object{m_dataToPrepare.front()};

    json graph, data;

    for (auto itr = (*object).begin(); itr != (*object).end(); ++itr) {
      if (itr.key() == "tid") {
        graph["tid"] = itr.value();
        data["tid"] = itr.value();
      } else if (itr.key() == "isDone") {
        std::lock_guard<std::mutex> lg{m_mMutex};
        m_gotLastMessage = (itr.value() == "1");
      } else if (itr.key() == "graph") {
        graph["graph"] = itr.value();
      } else {
        if(!itr.key().empty()) {
          data[itr.key()] = itr.value();
        }
      }
    }

    {
      std::lock_guard<std::mutex> lg{m_mMutex};
      m_dataToPrepare.pop();
    }

    {
      std::lock_guard<std::mutex> lg{m_mMutex};
      m_dataToAdd.push(&data);
      m_graphsToAdd.push(&graph);
    }
  }

  void DataParser::workOnData(DataParser &parser, DataStore::DataManager &dManager) {
    while (!(parser.m_gotLastMessage && parser.m_dataToAdd.empty())) {
      if (!parser.m_dataToAdd.empty()) {
        parser.addData(dManager);
      }
    }
  }

  void DataParser::addData(DataStore::DataManager &dManager) {
    dManager.addData(*m_dataToAdd.front());
    {
      std::lock_guard<std::mutex> lg{m_mMutex};
      m_dataToAdd.pop();
    }
  }

  void DataParser::workOnGraphs(DataParser &parser, GraphManager &gManager) {
    while (!(parser.m_gotLastMessage && parser.m_graphsToAdd.empty())) {
      if (!parser.m_graphsToAdd.empty()) {
        parser.addGraph(gManager);
      }
    }
  }

  void DataParser::addGraph(GraphManager &gManager) {
    gManager.addGraphFromPoints(*m_graphsToAdd.front());
    {
      std::lock_guard<std::mutex> lg{m_mMutex};
      m_graphsToAdd.pop();
    }
  }
}