#include "Module.hpp"

#include <utility>

namespace CAEMonitoringTool::DataStore {

  using std::isinf;
  using std::isnan;

  Module::Module(std::string name, double sum_rt, double max_rt, double avg_rt, double sum_vs, double sum_is) :
  m_name{std::move(name)}, m_sum_rt{sum_rt}, m_max_rt{max_rt}, m_avg_rt{avg_rt}, m_sum_vs{sum_vs}, m_sum_is{sum_is} {}

  Module::Module() : m_sum_rt{0.0}, m_max_rt{0.0}, m_avg_rt{0.0}, m_sum_vs{0.0}, m_sum_is{0.0} {}

  std::pair<bool, Module> Module::make(const std::string& name, double sum_rt, double max_rt,
                                        double avg_rt, double sum_vs, double sum_is) {
    if(name.empty()) {
      return std::pair{false, Module()};
    }
    if(sum_rt < 0 || isnan(sum_rt) || isinf(sum_rt)) {
      return std::pair{false, Module()};
    }
    if(max_rt < 0 || isnan(max_rt) || isinf(max_rt)) {
      return std::pair{false, Module()};
    }
    if(avg_rt < 0 || isnan(avg_rt) || isinf(avg_rt) || avg_rt > max_rt) {
      return std::pair{false, Module()};
    }
    if(sum_vs < 0 || isnan(sum_vs) || isinf(sum_vs)) {
      return std::pair{false, Module()};
    }
    if(sum_is < 0 || isnan(sum_is) || isinf(sum_is)) {
      return std::pair{false, Module()};
    }
    return std::pair{true, Module(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is)};
  }

}
