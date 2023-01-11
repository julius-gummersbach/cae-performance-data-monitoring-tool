#pragma once
#include "GraphOperation.hpp"
#include <stdexcept>
#include <queue>


namespace Graph
{
	class GraphDivision:GraphOperation
	{
	public:
		/**
		* Combines two Graphs mathematically
		*
		* @param firstGraph
		* @param secondGraph
		* @return the combined graph
		*/
		Graph evaluate(const Graph& firstGraph, const Graph& secondGraph);

	private:
		/**
		* Checks if the two types are compatible
		*
		* @param firstGraphDataType
		* @param secondGraphDataType
		* @return whether or not the types are compatible
		*/
		bool checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType);
	};
}
