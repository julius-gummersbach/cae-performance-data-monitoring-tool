include_directories(${CMAKE_HOME_DIRECTORY}/../../json-develop/include)

add_library(datastore
        DataManager.cpp
        DataManager.hpp
        ThreadInfo.cpp
        ThreadInfo.hpp)