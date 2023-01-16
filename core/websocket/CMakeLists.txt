#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/CAE-DUALSTUDIS/CLionProjects/boostLibrary/boost_1_81_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/CAE-DUALSTUDIS/CLionProjects/boostLibrary/boost_1_81_0/libs")
find_package(Boost 1.81.0)

#if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})
#add_executable(boostBeastTest.cpp boostBeastTest.cpp)
#target_link_libraries(boostBeastTest.cpp ws2_32)
#target_link_libraries(boostBeastTest.cpp ${Boost_LIBRARIES})

#include_directories(${CMAKE_HOME_DIRECTORY}/../../json-develop/include)

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/CAE-DUALSTUDIS/CLionProjects/json")
#find_package(nlohmann_json 3.11.2 REQUIRED)

include_directories(../../../websocketpp)
add_library(websocket
        websocket_endpoint.cpp
        connection_metadata.cpp
        test.cpp)
add_executable(test test.cpp)
#target_link_libraries(websocket_endpoint.hpp ${Boost_LIBRARIES})
#target_link_libraries(connection_metadata.hpp ${Boost_LIBRARIES})
#target_link_libraries(test.cpp ws2_32)
#target_link_libraries(test.cpp ${Boost_LIBRARIES})
#target_link_libraries(websocket nlohmann_json::nlohmann_json)
target_link_libraries(websocket ws2_32)
target_link_libraries(test websocket)
target_link_libraries(websocket ${Boost_LIBRARIES})
#endif()
