#include "ThreadInfo.hpp"

#include <memory>
#include <utility>
#include <cmath>
#include <stdexcept>

using std::isinf;
using std::isnan;
using std::string;
using std::invalid_argument;
using Graph::time_point;

namespace CAEMonitoringTool::DataStore {

    ThreadInfo::ThreadInfo(string threadId, string name, time_point startTime, double freq, int iterations,
                           int overruns, double sumRt) :
            m_threadId{std::move(threadId)}, m_name{std::move(name)}, m_startTime{startTime}, m_freq{freq},
            m_iterations{iterations}, m_overruns{overruns}, m_sumRt{sumRt} {
        // if parameters are invalid we throw an exception that should be caught by the GUI that should prompt the user for new input
        if (!(m_freq > 0 && !isinf(m_freq) && !isnan(m_freq))) {
            throw invalid_argument(
                    "ThreadInfo instance could not be created: invalid frequency: " + std::to_string(m_freq));
        }
        if (m_threadId.length() != 6
            || m_threadId.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
            throw invalid_argument("ThreadInfo instance could not be created: invalid thread id: " + m_threadId);
        }
        if (m_name.empty()) {
            throw invalid_argument("ThreadInfo instance could not be created: name must not be empty");
        }
        if (iterations < 0 || isinf(iterations) || isnan(iterations)) {
            throw invalid_argument("ThreadInfo instance could not be created: invalid value for iterations: "
                                   + std::to_string(iterations));
        }
        if (overruns < 0 || isinf(overruns) || isnan(overruns)) {
            throw invalid_argument("ThreadInfo instance could not be created: invalid value for overruns: "
                                   + std::to_string(overruns));
        }
        if (sumRt < 0 || isinf(sumRt) || isnan(sumRt)) {
            throw invalid_argument("ThreadInfo instance could not be created: invalid value for sumRT: "
                                   + std::to_string(sumRt));
        }
    }

    void ThreadInfo::addData(const string &name,
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
            m_sumRt += sumRt;
        }
        // we also store invalid data to be able to keep track of time
        m_data.push_back(std::make_shared<ThreadData>(name, isValid, sumRt, maxRt, avgRt, sumVs, sumIs));
    }

    void ThreadInfo::increaseOverruns(int delta) {
        m_overruns += delta;
    }

    const string &ThreadInfo::getThreadId() const {
        return m_threadId;
    }

    const string &ThreadInfo::getName() const {
        return m_name;
    }

    const Graph::time_point &ThreadInfo::getStartTime() const {
        return m_startTime;
    }

    double ThreadInfo::getFreq() const {
        return m_freq;
    }

    int ThreadInfo::getIterations() const {
        return m_iterations;
    }

    int ThreadInfo::getOverruns() const {
        return m_overruns;
    }

    double ThreadInfo::getSumRt() const {
        return m_sumRt;
    }

    const std::vector<std::shared_ptr<ThreadData>> &ThreadInfo::getData() const {
        return m_data;
    }

}