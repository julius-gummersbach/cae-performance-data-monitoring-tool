#include <map>
#include <nlohmann/json.hpp>
#include "ThreadData.h"
#include <iostream>

using json = nlohmann::json;
using std::map;
using std::cout;
using std::endl;

class DataManager {

  map<char*, ThreadData> map;

  public :
    bool addThreadInfo(json object) {
      cout << object << endl;
      return true;
    }

};