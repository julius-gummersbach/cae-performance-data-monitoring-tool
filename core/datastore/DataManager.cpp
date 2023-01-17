#include "DataManager.hpp"

std::deque<double> MonitoringTool::DataManager::getPointsInIntervall(const std::string &id,
                                                const Graph::time_point &startTime,
                                                const Graph::time_delta &length,
                                                const Graph::GraphDataType &type) const {

  const ThreadInfo info{m_threadInfos.at(id)};
  const std::vector<std::shared_ptr<ThreadData>> data{info.getData()};

  switch (type) {
    case Graph::GraphDataType::DATA_SUM_RT : {
      long long startIndex = (long long)((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
      if (data.size() < startIndex) {
        return std::deque<double>{};
      }
      long long duration = (long long) (length * info.getFreq() / 1000000000).count();
      std::deque<double> result{};
      while (duration < 0 || startIndex < data.size()) {
        result.push_front(data[startIndex+duration]->getSumRt());
        --duration;
      }
    }
    case Graph::GraphDataType::MAX_RT : {
      long long startIndex = (long long)((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
      if (data.size() < startIndex) {
        return std::deque<double>{};
      }
      long long duration = (long long) (length * info.getFreq() / 1000000000).count();
      std::deque<double> result{};
      while (duration < 0 || startIndex < data.size()) {
        result.push_front(data[startIndex+duration]->getMaxRt());
        --duration;
      }
    }
    case Graph::GraphDataType::AVG_RT : {
      long long startIndex = (long long)((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
      if (data.size() < startIndex) {
        return std::deque<double>{};
      }
      long long duration = (long long) (length * info.getFreq() / 1000000000).count();
      std::deque<double> result{};
      while (duration < 0 || startIndex < data.size()) {
        result.push_front(data[startIndex+duration]->getAvgRt());
        --duration;
      }
    }
    case Graph::GraphDataType::SUM_VS : {
      long long startIndex = (long long)((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
      if (data.size() < startIndex) {
        return std::deque<double>{};
      }
      long long duration = (long long) (length * info.getFreq() / 1000000000).count();
      std::deque<double> result{};
      while (duration < 0 || startIndex < data.size()) {
        result.push_front(data[startIndex+duration]->getSumVs());
        --duration;
      }
    }
    case Graph::GraphDataType::SUM_IS : {
      long long startIndex = (long long)((startTime - info.getStartTime()) * info.getFreq() / 1000000000).count();
      if (data.size() < startIndex) {
        return std::deque<double>{};
      }
      long long duration = (long long) (length * info.getFreq() / 1000000000).count();
      std::deque<double> result{};
      while (duration < 0 || startIndex < data.size()) {
        result.push_front(data[startIndex+duration]->getSumIs());
        --duration;
      }
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