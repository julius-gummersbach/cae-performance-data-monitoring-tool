#include "ThreadInfo.hpp"

using std::isinf;
using std::isnan;
using std::string;
using std::invalid_argument;

namespace CAEMonitoringTool::DataStore {

  ThreadInfo::ThreadInfo(string threadId, string name, const double &freq, const int &iterations,
                         const int &overruns, const double &sumRt, std::string jsonStr) :
          m_threadId{std::move(threadId)}, m_name{std::move(name)}, m_freq{freq},
          m_iterations{iterations}, m_overruns{overruns}, m_sumRt{sumRt}, m_jsonStr(std::move(jsonStr)) {};

  ThreadInfo::ThreadInfo() : m_freq{0.0}, m_iterations{0},
  m_overruns{0}, m_sumRt{0.0} {}

  ThreadInfo::operator string() const {
    return this->m_jsonStr;
  }

  std::pair<bool, ThreadInfo> ThreadInfo::make(const string& threadId, const string& name, const double &freq,
                                               const int &iterations, const int &overruns, const double &sumRt,
                                               const string& jsonStr) {

    if (!(freq > 0 && !isinf(freq) && !isnan(freq))) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    if (threadId.empty()) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    if (name.empty()) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    if (iterations < 0 ) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    if (overruns < 0 ) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    if (sumRt < 0 || isinf(sumRt) || isnan(sumRt)) {
      return std::pair<bool, ThreadInfo>{false, ThreadInfo()};
    }
    return std::pair<bool, ThreadInfo>{true, ThreadInfo(threadId, name, freq, iterations, overruns, sumRt, jsonStr)};
  }
}