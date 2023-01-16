#include "ThreadInfo.hpp"

#include <memory>
#include <utility>
#include <cmath>
#include <stdexcept>

using std::isinf;
using std::isnan;
using std::string;

MonitoringTool::ThreadInfo::ThreadInfo(string threadId, string name, time_point startTime, double freq) :
        m_threadId{std::move(threadId)}, m_name{std::move(name)}, m_startTime{startTime}, m_freq{freq}, m_iterations{0},
        m_overruns{0}, m_sumRt{0} {
    // if parameters are invalid we throw an exception that should be caught by the GUI that should prompt the user for new input
    if (!(m_freq > 0 && !isinf(m_freq) && !isnan(m_freq))) {
        throw std::invalid_argument("ThreadInfo instance could not be created: invalid frequency: " + std::to_string(m_freq));
    }
    if (m_threadId.length() != 6
    || m_threadId.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
        throw std::invalid_argument("ThreadInfo instance could not be created: invalid thread id: " + m_threadId);
    }
    if (m_name.empty()) {
        throw std::invalid_argument("ThreadInfo instance could not be created: name must not be empty");
    }
}

void MonitoringTool::ThreadInfo::addData(const string &name,
                         double sumRt,
                         double maxRt,
                         double avgRt,
                         double sumVs,
                         double sumIs) {
    bool isValid = name == m_name
                   // check for infinity and nan
                   && !isinf(sumRt) && !isnan(sumRt) && sumRt > 0
                   && !isinf(maxRt) && !isnan(maxRt) && maxRt > 0
                   && !isinf(avgRt) && !isnan(avgRt) && avgRt > 0
                   && !isinf(sumVs) && !isnan(sumVs) && sumVs > 0 // todo revise as soon as content is clarified
                   && !isinf(sumIs) && !isnan(sumIs) && sumIs > 0 // todo revise as soon as content is clarified
                   // check for logical content
                   && sumRt >= maxRt && maxRt >= avgRt * 1000; // avgRt is in ms while maxRt is in s
    if (isValid) {
        // todo update overruns
        m_sumRt += sumRt;
    }
    // we also store invalid data to be able to keep track of time
    m_data.push_back(std::make_shared<ThreadData>(name, isValid, sumRt, maxRt, avgRt, sumVs, sumIs));
}

const string &MonitoringTool::ThreadInfo::getThreadId() const {
    return m_threadId;
}

const string &MonitoringTool::ThreadInfo::getName() const {
    return m_name;
}

double MonitoringTool::ThreadInfo::getFreq() const {
    return m_freq;
}

int MonitoringTool::ThreadInfo::getIterations() const {
    return m_iterations;
}

int MonitoringTool::ThreadInfo::getOverruns() const {
    return m_overruns;
}

double MonitoringTool::ThreadInfo::getSumRt() const {
    return m_sumRt;
}
