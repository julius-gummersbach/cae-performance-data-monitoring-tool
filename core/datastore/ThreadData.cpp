#include "ThreadData.hpp"

#include <utility>

using std::string;


MonitoringTool::ThreadData::ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs, double sumIs) :
                       m_name(std::move(name)), m_isValid(isValid), m_sumRt(sumRt), m_maxRt(maxRt), m_avgRt(avgRt),
                       m_sumVs(sumVs), m_sumIs(sumIs) {
}

const string &MonitoringTool::ThreadData::getName() const {
    return m_name;
}

bool MonitoringTool::ThreadData::isValid() const {
    return m_isValid;
}

double MonitoringTool::ThreadData::getSumRt() const {
    return m_sumRt;
}

double MonitoringTool::ThreadData::getMaxRt() const {
    return m_maxRt;
}

double MonitoringTool::ThreadData::getAvgRt() const {
    return m_avgRt;
}

double MonitoringTool::ThreadData::getSumVs() const {
    return m_sumVs;
}

double MonitoringTool::ThreadData::getSumIs() const {
    return m_sumIs;
}
