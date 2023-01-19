
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../../../boostlibrary/boost_1_81_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "../../../boostlibrary/boost_1_81_0/libs")
find_package(Boost 1.81.0)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../../json/include)
include_directories(../../../websocketpp)

add_library(websocket
        WebsocketEndpoint.cpp
        ConnectionMetadata.cpp
        test.cpp)

add_executable(test test.cpp)
target_link_libraries(websocket ws2_32)
target_link_libraries(test websocket)
target_link_libraries(websocket ${Boost_LIBRARIES})

