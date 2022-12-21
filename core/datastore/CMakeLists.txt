find_package(nlohmann_json 3.2.0 REQUIRED)
add_library(datastore DataManager.cpp WebSocketConnector.cpp)

target_link_libraries(datastore PRIVATE nlohmann_json::nlohmann_json)
