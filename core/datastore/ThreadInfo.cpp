#include "ThreadInfo.hpp"

#include <memory>
#include <utility>
#include <cmath>
#include <stdexcept>

using std::isinf;
using std::isnan;
using std::string;
using std::invalid_argument;

namespace CAEMonitoringTool::DataStore {

  ThreadInfo::ThreadInfo(string threadId, string name, const double &freq, const int &iterations,
                         const int &overruns, const double &sumRt) :

          m_threadId{std::move(threadId)}, m_name{std::move(name)}, m_freq{freq},
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
}