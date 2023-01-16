#include "DataManager.hpp"
#include "../dataprocessing/DataTypes.hpp"

deque<double> DataManager::getPointsInIntervall(const string &id,
                                                const Graph::timePoint &startTime,
                                                const Graph::time_delta &length,
                                                const Graph::GraphDataType &type) const {

  const ThreadInfo info = m_threadInfos.at(id);

  switch (type) {
    case Graph::GraphDataType::DATA_SUM_RT : {

    }
    case Graph::GraphDataType::INFO_SUM_RT : {
      return std::deque<double>{info.getSumRt()};
    }
    case Graph::GraphDataType::MAX_RT : {

    }
    case Graph::GraphDataType::AVG_RT : {

    }
    case Graph::GraphDataType::SUM_VS : {

    }
    case Graph::GraphDataType::SUM_IS : {

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