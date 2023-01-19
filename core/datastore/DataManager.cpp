#include "DataManager.hpp"

namespace CAEMonitoringTool::DataStore {

  std::deque<double> DataManager::getData(const ThreadInfo &info,
                                                                     const std::vector<std::shared_ptr<ThreadData>> &data,
                                                                     const Graph::time_point &startTime,
                                                                     const Graph::time_delta &length,
                                                                     const DataManager::getterFunc &func) {
    long long startIndex = (long long) ((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
    if (data.size() < startIndex) {
      return std::deque<double>{};
    }
    long long duration = (long long) (length * info.getFreq() / 1000000000).count();
    std::deque<double> result{};
    while (duration < 0 || startIndex < data.size()) {
      result.push_front(func(*data[startIndex + duration].get()));
      --duration;
    }
    return result;
  }

  std::deque<double> DataManager::getPointsInIntervall(const std::string &id,
                                                                                  const Graph::time_point &startTime,
                                                                                  const Graph::time_delta &length,
                                                                                  const Graph::GraphDataType &type) const {

    const ThreadInfo info{m_threadInfos.at(id)};
    const std::vector<std::shared_ptr<ThreadData>> data{info.getData()};

    switch (type) {
      case Graph::GraphDataType::DATA_SUM_RT : {
        std::deque<double> result{
                getData(info, data, startTime, length, DataManager::getSumRT)};
        return result;
      }
      case Graph::GraphDataType::MAX_RT : {
        std::deque<double> result{
                getData(info, data, startTime, length, DataManager::getMaxRT)};
        return result;
      }
      case Graph::GraphDataType::AVG_RT : {
        std::deque<double> result{
                getData(info, data, startTime, length, DataManager::getAvgRT)};
        return result;
      }
      case Graph::GraphDataType::SUM_VS : {
        std::deque<double> result{
                getData(info, data, startTime, length, DataManager::getSumVS)};
        return result;
      }
      case Graph::GraphDataType::SUM_IS : {
        std::deque<double> result{
                getData(info, data, startTime, length, DataManager::getSumIS)};
        return result;
      }
      case Graph::GraphDataType::INFO_SUM_RT : {
        return std::deque<double>{info.getSumRt()};
      }
      case Graph::GraphDataType::FREQ : {
        return std::deque<double>{info.getFreq()};
      }
      case Graph::GraphDataType::ITERATIONS : {
        return std::deque<double>{(double) info.getIterations()};
      }
      case Graph::GraphDataType::OVERRUNS : {
        return std::deque<double>{(double) info.getOverruns()};
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