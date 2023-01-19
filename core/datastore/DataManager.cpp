#include "DataManager.hpp"

namespace CAEMonitoringTool::DataStore {

  void DataManager::addThreadInfo(const json &object) {
    if (m_threadInfos.find(object["tid"]) == m_threadInfos.end()) {
      ThreadInfo info = getInfo(object);
      vector<json> data = object["data"];
      for (const json &j: data) {
        addThreadData(info, j);
      }
      m_threadInfos.insert_or_assign(info.getThreadId(), info);
    } else {
      if (std::basic_string.equal(m_threadInfos.at(object["tid"]).getName(), object["name"]) {
        vector<json> data = object["data"];
        ThreadInfo &pInfo = m_threadInfos.at(object["tid"]);
        pInfo.increaseOverruns(object["overruns"]);
        for (const json &object: data) {
          addThreadData(pInfo, object);
        }
      } else {
        // TODO: warning here that id was not unique
      }
    }
  }

  void DataManager::addThreadData(ThreadInfo &info, const json &object) {
    string name = object["name"];
    vector<double> sum_rt = object["sum_rt"];
    vector<double> max_rt = object["max_rt"];
    vector<double> avg_rt = object["avg_rt"];
    double sum_vs = object["sum_vs"];
    double sum_is = object["sum_is"];
    info.addData(name, sum_rt.front(), max_rt.front(), avg_rt.front(), sum_vs, sum_is);
  }

  ThreadInfo DataManager::getInfo(const json &object) {
    Graph::timePoint startTime = std::chrono::system_clock::now();
    string tid = object["tid"];
    string name = object["name"];
    double freq = object["freq"];
    int iterations = object["iterations");
    int overruns = object["overruns");
    vector<double> sum_rt = object["sum_rt");

    ThreadInfo info{tid, name, freq, startTime, freq, iterations, overruns};
    return info;
  }
}