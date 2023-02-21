#pragma once

#include "DataTypes.hpp"
#include "ImageGeneration\ImageGenerator.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	class Graph
	{
	private:
		std::vector<std::pair<int, double>>	m_dataPoints;// the points that make up the graph
		std::string m_svgPath;
		std::string m_threadId;

	public:
		/**
		* Creates a graph wrapping the points given.
		*
		* @param dataPoints the points that make up the graph.
		* @param threadId of the given points
		*/
		Graph(const std::vector<std::pair<int, double>>& dataPoints, const std::string& threadId);

		/**
		* Combines two graphs with the given Operation and creates a new Graph with the given threadId.
		*
		* @param leftGraph a Graph to combine
		* @param rightGraph a Graph to combine
		* @param threadId for the new Graph
		* @param operationFunction to use on the two graphs
		*/
		Graph(const Graph& leftGraph, const Graph& rightGraph, const std::string& threadId, operationFunction operationFunction);

		/**
		* Generates a SVG-file and returns the path of this file.
		*
		* @param string threadId
		* @return string that specifies the path to the generated svg-file
		*/
		const std::string& getImage();
	};
}
