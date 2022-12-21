find_package(nlohmann_json 3.2.0 REQUIRED) # todo package isn't found
add_library(datastore DataManager.cpp WebSocketConnector.cpp ThreadData.h ThreadInfo.h ThreadInfo.cpp WebSocketConnector.h ThreadData.cpp DataManager.h)

target_link_libraries(datastore PRIVATE nlohmann_json::nlohmann_json)
