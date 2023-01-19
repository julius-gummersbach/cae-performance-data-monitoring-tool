#include "DataManager.hpp"

std::deque<double> MonitoringTool::DataStore::DataManager::getData(const ThreadInfo &info,
                                                                   const std::vector<std::shared_ptr<ThreadData>> &data,
                                                                   const Graph::time_point &startTime,
                                                                   const Graph::time_delta &length,
                                                                   const MonitoringTool::DataStore::DataManager::getterFunc &func) {
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

std::deque<double> MonitoringTool::DataStore::DataManager::getPointsInIntervall(const std::string &id,
                                                                                const Graph::time_point &startTime,
                                                                                const Graph::time_delta &length,
                                                                                const Graph::GraphDataType &type) const {

  const ThreadInfo info{m_threadInfos.at(id)};
  const std::vector<std::shared_ptr<ThreadData>> data{info.getData()};

  switch (type) {
    case Graph::GraphDataType::DATA_SUM_RT : {
      std::deque<double> result{getData(info,  data, startTime, length, MonitoringTool::DataStore::DataManager::getSumRT)};
      return result;
    }
    case Graph::GraphDataType::MAX_RT : {
      std::deque<double> result{getData(info,  data, startTime, length, MonitoringTool::DataStore::DataManager::getMaxRT)};
      return result;
    }
    case Graph::GraphDataType::AVG_RT : {
      std::deque<double> result{getData(info,  data, startTime, length, MonitoringTool::DataStore::DataManager::getAvgRT)};
      return result;
    }
    case Graph::GraphDataType::SUM_VS : {
      std::deque<double> result{getData(info,  data, startTime, length, MonitoringTool::DataStore::DataManager::getSumVS)};
      return result;
    }
    case Graph::GraphDataType::SUM_IS : {
      std::deque<double> result{getData(info,  data, startTime, length, MonitoringTool::DataStore::DataManager::getSumIS)};
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

const double &MonitoringTool::DataStore::DataManager::getSumRT(const MonitoringTool::ThreadData &data) {
  return data.m_sumRt;
}

const double &MonitoringTool::DataStore::DataManager::getMaxRT(const MonitoringTool::ThreadData &data) {
  return data.m_maxRt;
}

const double &MonitoringTool::DataStore::DataManager::getAvgRT(const MonitoringTool::ThreadData &data) {
  return data.m_avgRt;
}

const double &MonitoringTool::DataStore::DataManager::getSumVS(const MonitoringTool::ThreadData &data) {
  return data.m_sumVs;
}

const double &MonitoringTool::DataStore::DataManager::getSumIS(const MonitoringTool::ThreadData &data) {
  return data.m_sumIs;
}

