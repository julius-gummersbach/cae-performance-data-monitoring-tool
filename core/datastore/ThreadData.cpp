#include "ThreadData.hpp"

#include <utility>

using std::string;


ThreadData::ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs, double sumIs) :
                       m_name(std::move(name)), m_isValid(isValid), m_sumRt(sumRt), m_maxRt(maxRt), m_avgRt(avgRt),
                       m_sumVs(sumVs), m_sumIs(sumIs) {
}

const string &ThreadData::getName() const {
    return m_name;
}

bool ThreadData::isValid() const {
    return m_isValid;
}

double ThreadData::getSumRt() const {
    return m_sumRt;
}

double ThreadData::getMaxRt() const {
    return m_maxRt;
}

double ThreadData::getAvgRt() const {
    return m_avgRt;
}

double ThreadData::getSumVs() const {
    return m_sumVs;
}

double ThreadData::getSumIs() const {
    return m_sumIs;
}
