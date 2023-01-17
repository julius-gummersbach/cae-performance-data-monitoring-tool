#include "ThreadData.hpp"

#include <utility>

using std::string;

namespace MonitoringTool::DataStore {

    ThreadData::ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs,
                                      double sumIs) :
            m_name(std::move(name)), m_isValid(isValid), m_sumRt(sumRt), m_maxRt(maxRt), m_avgRt(avgRt),
            m_sumVs(sumVs), m_sumIs(sumIs) {
    }
}