#include "GraphAddition.hpp"

namespace Graph {

	Graph evaluate(const Graph& firstGraph, const Graph& secondGraph)
	{
		
		if(!checkTypeCompatibility(firstGraph.getDataPoints(), secondGraph.getDataPoints()))
		{
			
		}


	}
	bool checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType);
}