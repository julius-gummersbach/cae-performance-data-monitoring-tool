#include "DataManager.hpp"

void DataManager::addThreadInfo(const json &object) {
  if (m_threadInfos.find(object["tid"]) == m_threadInfos.end()) {
    ThreadInfo info = getInfo(object);
    vector<json> data = object["data"];
    for (const json &j: data) {
      addThreadData(info, j);
    }
    m_threadInfos.insert_or_assign(info.getThreadId(), info);
  } else {
    if (m_threadInfos.at(object[tid]).getName().equal(object["name"])) {
      vector<json> data = object["data"];
      ThreadInfo &pInfo = m_threadInfos.at(object["tid"]);
      for (const json &j: data) {
        addThreadData(pInfo, j);
      }
    } else {
      // TODO: warning here that id was not unique
    }
  }
}

const pair<bool, ThreadInfo> &DataManager::getDataFromId(const string &id) {

  pair<bool, ThreadInfo> p{true,
                           ThreadInfo{"foo",
                                      "bar",
                                      static_cast<double>(rand() % 100)}};
  return p;

  //TODO: comment back in once real data is usable and delete rng
  /*
  if (m_threadInfos.find(id) == m_threadInfos.end()) {
    pair<bool, ThreadInfo> p{true, m_threadInfos.at(id)};
    return p;
  } else {
    pair<bool, ThreadInfo> p{false, ThreadInfo{0,nullptr,0}};
    return p;
  }
  */
}

const pair<bool, ThreadInfo> &DataManager::operator[](const string &id) const {
  return getDataFromId(id);
}

void DataManager::addThreadData(ThreadInfo &info, const json &j) {
  string name = j["name"];
  vector<double> sum_rt = j["sum_rt"];
  vector<double> max_rt = j["max_rt"];
  vector<double> avg_rt = j["avg_rt"];
  double sum_vs = j["sum_vs"];
  double sum_is = j["sum_is"];
  info.addData(name, sum_rt.front(), max_rt.front(), avg_rt.front(), sum_vs, sum_is);
}

ThreadInfo DataManager::getInfo(const json &object) {
  string tid = object["tid"];
  string name = object["name"];
  double freq = object["freq"];

  // TODO: determine what to do with these parameters
  // int iterations = object["iterations");
  // int overruns = object["overruns");
  // vector<double> sum_rt = object["sum_rt");

  ThreadInfo info{tid, name, freq};
  return info;
}