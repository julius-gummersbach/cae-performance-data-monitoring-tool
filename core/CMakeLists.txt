PROJECT(CAE_Performance_Data_Monitoring_Tool)
cmake_minimum_required(VERSION 3.0)
# These directories must not be added to git!
# DEBUG compile targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG build/debug)
# RELEASE compile targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE build/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE build/release)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../boostlibrary/boost_1_81_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "../../boostlibrary/boost_1_81_0/libs")

find_package(Boost 1.81.0)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../json/include)
include_directories(../../websocketpp)

add_subdirectory(main)
add_subdirectory(dataprocessing)
add_subdirectory(datastore)

set(CMAKE_CXX_STANDARD 20)

add_library(websocket
        websocket/WebsocketEndpoint.cpp
        websocket/ConnectionMetadata.cpp
        main/Controller.cpp)

add_executable(run main/Controller.cpp)
target_link_libraries(websocket ws2_32)
target_link_libraries(websocket wsock32)
target_link_libraries(run websocket)
target_link_libraries(run dataprocessing)
target_link_libraries(run datastore)
target_link_libraries(websocket ${Boost_LIBRARIES})


