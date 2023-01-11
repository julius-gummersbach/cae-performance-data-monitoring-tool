#include "GraphAddition.hpp"

namespace Graph {

	Graph GraphAddition::evaluate(const Graph& firstGraph, const Graph& secondGraph)
	{
		if(!checkTypeCompatibility(firstGraph.getType(), secondGraph.getType()))
		{
			//throw
		}


		return firstGraph;
	}
	bool GraphAddition::checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType)
	{
		return true;
	}
}