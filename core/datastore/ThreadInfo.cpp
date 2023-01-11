#include "ThreadInfo.h"

#include <utility>
#include <cmath>
#include <stdexcept>

using std::isinf;
using std::isnan;
using std::string;

ThreadInfo::ThreadInfo(long threadId, string name, double freq) :
        m_threadId{threadId}, m_name{std::move(name)}, m_freq{freq}, m_iterations{0}, m_overruns{0}, m_sumRt{0} {
    // if parameters are invalid we throw an exception that should be caught by the GUI that should prompt the user for new input
    if (!(m_freq > 0 && !isinf(m_freq) && !isnan(m_freq))) {
        throw std::invalid_argument("ThreadInfo instance could not be created: invalid frequency: " + std::to_string(m_freq));
    }
    if(isnan(m_threadId)) {
        throw std::invalid_argument("ThreadInfo instance could not be created: thread id was NAN ");
    }
    if(isinf(m_threadId)){
        throw std::invalid_argument("ThreadInfo instance could not be created: thread id was infinity");
    }
    if(m_name.empty()){
        throw std::invalid_argument("ThreadInfo instance could not be created: name must not be empty");
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
        // todo update overruns
        m_sumRt += sumRt;
    }
    // we also store invalid data to be able to keep track of time
    m_data.emplace_back(name, isValid, sumRt, maxRt, avgRt, sumVs, sumIs);
}
