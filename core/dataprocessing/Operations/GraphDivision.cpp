#include "GraphDivision.hpp"

namespace CAEMonitoringTool::DataProcessing {

	Graph GraphDivision::evaluate(const Graph& firstGraph, const Graph& secondGraph)
	{
		if (!checkTypeCompatibility(firstGraph.getType(), secondGraph.getType()))
		{
			throw std::invalid_argument("GraphDataType is not compatible");
		}
		std::deque<double> newDataPoints{};

		auto first = firstGraph.getDataPoints().begin();
		auto firstEnd = firstGraph.getDataPoints().end();
		auto second = secondGraph.getDataPoints().begin();

		while (first != firstEnd)
		{
			newDataPoints.push_back(*first / *second);
			first++;
			second++;
		}
		return Graph{ newDataPoints, firstGraph.getType() };
	}
	bool GraphDivision::checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType)
	{
		return firstGraphDataType == secondGraphDataType;
	}
}