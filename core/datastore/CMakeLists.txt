# add_library(datastore <source files here>)

add_library(datastore DataManager.cpp ThreadInfo.cpp ThreadData.cpp WebSocketConnector.cpp)

add_library(DataManager.h ThreadData.h ThreadInfo.h WebSocketConnector.h)

include_directories(../../../json-develop/include)