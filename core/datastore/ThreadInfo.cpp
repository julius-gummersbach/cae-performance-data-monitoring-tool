#include "ThreadInfo.hpp"

#include <utility>
#include <cmath>

using std::isinf;
using std::isnan;
using std::string;

ThreadInfo::ThreadInfo(string threadId, string name, double freq, Graph::timePoint startTime) :
        m_threadId{threadId},
        m_name{std::move(name)},
        m_startTime{startTime},
        m_freq{freq}, m_iterations{0},
        m_overruns{0}, m_sumRt{0} {
  if (!(m_freq == 60 && !m_name.empty())) {
    // todo log error and throw exception
  }
}

void ThreadInfo::addData(const string &name,
                         double sumRt,
                         double maxRt,
                         double avgRt,
                         double sumVs,
                         double sumIs) {
  bool isValid = !m_name.empty()
                 // check for infinity and nan
                 && !isinf(sumRt) && !isnan(sumRt) && sumRt > 0
                 && !isinf(maxRt) && !isnan(maxRt) && maxRt > 0
                 && !isinf(avgRt) && !isnan(avgRt) && avgRt > 0
                 && !isinf(sumVs) && !isnan(sumVs) && sumVs > 0 // todo revise as soon as content is clarified
                 && !isinf(sumIs) && !isnan(sumIs) && sumIs > 0 // todo revise as soon as content is clarified
                 // check for logical content
                 && sumRt >= maxRt && maxRt >= avgRt * 1000; // avgRt is in ms while maxRt is in s
  if (isValid) {
    m_iterations++; // todo is this correct?
    // todo update overruns
    m_sumRt += sumRt;
  }
  m_data.emplace_back(name, isValid, sumRt, maxRt, avgRt, sumVs, sumIs);
}

const string& ThreadInfo::getThreadId() const {
  return this->m_threadId;
}

const string& ThreadInfo::getName() const {
  return this->m_name;
}

const Graph::timePoint &ThreadInfo::getStartTime() const {
  return this->m_startTime;
}