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
      }
    }
  }

  const double &DataManager::getSumRT(const ThreadData &data) {
    return data.m_sumRt;
  }

  const double &DataStore::DataManager::getMaxRT(const ThreadData &data) {
    return data.m_maxRt;
  }

  const double &DataManager::getAvgRT(const ThreadData &data) {
    return data.m_avgRt;
  }

  const double &DataManager::getSumVS(const ThreadData &data) {
    return data.m_sumVs;
  }

  const double &DataManager::getSumIS(const ThreadData &data) {
    return data.m_sumIs;
  }

}
