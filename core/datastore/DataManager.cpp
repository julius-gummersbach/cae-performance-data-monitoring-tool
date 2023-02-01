#include "DataManager.hpp"

namespace CAEMonitoringTool::DataStore {

  void DataManager::addData(const json &object) {

    ThreadInfo info{object.at("tid"), object.at("name"), object.at("freq"),
                    object.at("iterations"), object.at("overruns"), object.at("sum_rt").at(0)};

    const std::vector<json> modules{object.at("modules")};
    for (auto &x: modules) {
      info.m_modules.push_back(std::make_shared<json>(x));
    }
    this->m_threadsInfos.emplace(info.m_threadId, info);
  }

  std::string DataManager::getModulesJSON(const std::string &id) const {
    if (m_threadsInfos.find(id) == m_threadsInfos.cend()) {
      std::string result;
      return result;
    } else {
      ThreadInfo info{m_threadsInfos.at(id)};
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

  std::vector<std::string> DataManager::getThreadIds() const {
    std::vector<string> keys;
    for(const auto &pair : m_threadsInfos) {
      keys.push_back(pair.first);
    }
    return keys;
  }
}
