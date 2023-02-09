include_directories(${CMAKE_HOME_DIRECTORY}/../../json-develop/include)

set(CMAKE_CXX_STANDARD 20)
add_library(dataprocessing
		Graph.cpp
		GraphManager.cpp
        DataParser.cpp
		ImageGeneration/PPlot.cpp
		ImageGeneration/SVGPainter.cpp
		ImageGeneration/ImageGenerator.cpp)

add_executable(imageGeneratorTest ImageGeneration/ImageGenerator.cpp)

target_link_libraries(imageGeneratorTest dataprocessing)

