include_directories(${CMAKE_HOME_DIRECTORY}/../../json/include)

set(CMAKE_CXX_STANDARD 20)

add_library(datastore
        DataManager.cpp
        ThreadInfo.cpp
        Module.cpp)
