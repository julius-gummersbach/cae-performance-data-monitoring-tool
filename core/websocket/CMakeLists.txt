include_directories(../../../json/include)

add_library(websocket
        WebsocketEndpoint.cpp
        ConnectionMetadata.cpp
        test.cpp)

add_executable(test test.cpp)
target_link_libraries(websocket ws2_32)
target_link_libraries(test websocket)

