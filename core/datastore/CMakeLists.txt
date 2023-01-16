add_library(datastore DataManager.cpp WebSocketConnector.cpp ThreadData.cpp ThreadInfo.cpp)

include_directories(../../../nlohmann_json/include)  # temporary solution, you need to clone the https://github.com/nlohmann/json.git repo and put the path here
