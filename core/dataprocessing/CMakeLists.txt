include_directories(${CMAKE_HOME_DIRECTORY}/../../json/include)

set(CMAKE_CXX_STANDARD 20)
add_library(dataprocessing
		Graph.cpp
		GraphManager.cpp
        DataParser.cpp
		ImageGeneration/PPlot.cpp
		ImageGeneration/SVGPainter.cpp
		ImageGeneration/ImageGenerator.cpp)