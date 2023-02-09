#include "Graph.hpp"

namespace CAEMonitoringTool::DataProcessing 
{
	Graph::Graph(const std::vector<std::pair<int, double>>& dataPoints) :m_dataPoints{ dataPoints }
	{}

	Graph::Graph(const Graph& leftGraph, const Graph& rightGraph, operationFunction operation)
	{
		std::vector<std::pair<int, double>>	newDataPoints{};

		auto leftIter = leftGraph.m_dataPoints.begin();
		auto leftEnd = leftGraph.m_dataPoints.end();
		auto rightIter = rightGraph.m_dataPoints.begin();

		while (leftIter != leftEnd)
		{
			newDataPoints.push_back(std::pair<int, double>{leftIter->first, operation(leftIter->second, rightIter->second)});
			++leftIter;
			++rightIter;
		}
		m_dataPoints = newDataPoints;
	}

	std::string Graph::getImage()
	{
		return "TODO";
	}
}