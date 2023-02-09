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
		* @param type the type of graph being created
		*/
		Graph(const std::vector<std::pair<int, double>>& dataPoints, const std::string& threadId);

		Graph(const Graph& leftGraph, const Graph& rightGraph, const std::string& threadId, operationFunction operationFunction);

		std::string getImage();
	};
}
