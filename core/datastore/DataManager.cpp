#include "DataManager.hpp"

namespace CAEMonitoringTool::DataStore {

  void DataManager::addData(const std::string &jsonString) {
    const json jsonObject{json::parse(jsonString)};

    ThreadInfo info{jsonObject["tid"], jsonObject["name"], jsonObject["freq"],
                    jsonObject["iterations"], jsonObject["overruns"], jsonObject["sum_rt"]};

    const std::vector<json> modules{jsonObject["modules"]};
    for (auto &x: modules) {
      info.m_modules.push_back(std::make_shared<json>(x));
    }
    this->m_threads.emplace(info.m_threadId, info);
  }

  std::string DataManager::getModulesJSON(const std::string &id) const {
    if (m_threads.find(id) == m_threads.cend()) {
      std::string result;
      return result;
    } else {
      ThreadInfo info{m_threads.at(id)};
      string result{"{"};
      string divider;
      for (const std::shared_ptr<json> &object: info.m_modules) {
        result.append(divider).append(object->dump());
        divider = ", ";
      }
      result.append("}");
      return result;
    }
  }


}