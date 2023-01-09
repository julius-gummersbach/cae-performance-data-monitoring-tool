#include "DataManager.h"

void DataManager::addThreadInfo(json object) {

  ThreadInfo info = getInfo(object);

  vector<json> data = object.at("data");
  for (const json &j: data) {
    addThreadData(info, j);
  }

  if(m_threadInfos.find(info.getThreadId()) == m_threadInfos.end()) {
    m_threadInfos.insert_or_assign(info.getThreadId(), vector<ThreadInfo>{info});
  } else {
    m_threadInfos.at(info.getThreadId()).emplace_back(info);
  }
}

ThreadInfo getDataFromID(long id) {

}

void DataManager::addThreadData(ThreadInfo &info, const json &j) const {
  string name = j.at("name");
  double sum_rt = j.at("sum_rt");
  double max_rt = j.at("max_rt");
  double avg_rt = j.at("avg_rt");
  double sum_vs = j.at("sum_vs");
  double sum_is = j.at("sum_is");
  info.addData(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is);
}

ThreadInfo DataManager::getInfo(const json &object) const {
  long tid = object.at("tid");
  string name = object.at("name");
  double freq = object.at("freq");

  // TODO: determine what to do with these parameters
  int iterations = object.at("iterations");
  int overruns = object.at("overruns");
  double sum_rt = object.at("sum_rt");

  ThreadInfo info{tid, name, freq};
  return info;
}