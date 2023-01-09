# add_library(datastore <source files here>)

include_directories(${CMAKE_HOME_DIRECTORY}/../../json-develop/include)

add_library(datastore
        DataManager.cpp
        DataManager.h
        ThreadInfo.cpp
        ThreadInfo.h
        ThreadData.cpp
        ThreadData.h
        WebSocketConnector.cpp
        WebSocketConnector.h)

