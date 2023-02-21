#include "DataManager.hpp"

namespace CAEMonitoringTool::DataStore {

  void DataManager::addData(const json &object) {

    auto infoObject{ThreadInfo::make(object["tid"], object["name"], object["freq"],
                                     object["iterations"], object["overruns"], object["sum_rt"],
                                     object.dump())};

    if(!infoObject.first) {
      std::cout << "A Thread with invalid data was detected." << std::endl;
      return;
    }

    auto& info{infoObject.second};

    for (auto &x: object["modules"]) {
      auto moduleObject{Module::make(x["name"], x["sum_rt"], x["max_rt"],
                                     x["avg_rt"], x["sum_vs"], x["sum_is"])};
      if(!moduleObject.first) {
        std::cout << "A Module with invalid data was detected." << std::endl;
        continue;
      }
      info.m_modules.push_back(std::make_shared<Module>(moduleObject.second));
    }

    this->m_threadsInfos.emplace(info.m_threadId, info);
  }

  std::vector<std::string> DataManager::getThreadIds() const {
    std::vector<string> keys;
    for(const auto &pair : m_threadsInfos) {
      keys.push_back(pair.first);
    }
    return keys;
  }

  std::string DataManager::getThreadInfo(const string &id) const {
    const std::vector<std::string> &keys = this->getThreadIds();
    if(std::find(keys.begin(), keys.end(), id) == keys.end()) {
      std::string result;
      return result;
    }
    return (std::string) m_threadsInfos.at(id);
  }
}
