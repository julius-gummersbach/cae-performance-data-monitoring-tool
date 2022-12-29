#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using std::map;

struct ThreadData {};

class DataManager {

    map<char*, ThreadData> map;

    bool addThreadInfo(json object) {
      // nicht lesen noch nicht implementiert
      // verpiss dich samuel
    }

};