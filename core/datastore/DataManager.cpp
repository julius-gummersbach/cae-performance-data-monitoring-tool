#include "DataManager.h"

void DataManager::addThreadInfo(json object) {
  if (m_threadInfos.find(object["tid"]) == m_threadInfos.end()) {
    ThreadInfo info = getInfo(object);
    vector<json> data = object["data"];
    for (const json &j: data) {
      addThreadData(info, j);
    }
    m_threadInfos.insert_or_assign(info.getThreadId(), info);
  } else {
    vector<json> data = object["data"];
    ThreadInfo &pInfo = m_threadInfos.at(object["tid"]);
    for (const json &j: data) {
      addThreadData(pInfo, j);
    }
  }
}

const pair<bool, ThreadInfo> &DataManager::getDataFromId(long id) {

  pair<bool, ThreadInfo> p{true,
                           ThreadInfo{rand() % 100,
                                      "foo",
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

const pair<bool,ThreadInfo>& DataManager::operator[](long id) const {
  return getDataFromId(id);
}

void DataManager::addThreadData(ThreadInfo &info, const json &j) {
  string name = j.at("name");
  double sum_rt = j.at("sum_rt");
  double max_rt = j.at("max_rt");
  double avg_rt = j.at("avg_rt");
  double sum_vs = j.at("sum_vs");
  double sum_is = j.at("sum_is");
  info.addData(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is);
}

ThreadInfo DataManager::getInfo(const json &object) {
  long tid = object.at("tid");
  string name = object.at("name");
  double freq = object.at("freq");

  // TODO: determine what to do with these parameters
  /*
  int iterations = object.at("iterations");
  int overruns = object.at("overruns");
  double sum_rt = object.at("sum_rt");
  */

  ThreadInfo info{tid, name, freq};
  return info;
}