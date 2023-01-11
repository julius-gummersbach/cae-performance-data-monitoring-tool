#include "GraphDivision.hpp"
#include <queue>

namespace Graph {

	Graph GraphDivision::evaluate(const Graph& firstGraph, const Graph& secondGraph)
	{
		if (!checkTypeCompatibility(firstGraph.getType(), secondGraph.getType()))
		{
			throw std::invalid_argument("GraphDataType is not compatible");
		}
		std::deque<double> newDataPoints{};

		auto& first = firstGraph.getDataPoints().begin();
		auto& second = secondGraph.getDataPoints().begin();
		auto& end = firstGraph.getDataPoints().end();

		while (first == end)
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