#pragma once
#include "GraphOperation.hpp"


namespace Graph
{
	class GraphAddition :GraphOperation
	{
	public:
		/**
		* Combines two Graphs mathematically.
		* Where each point from the combined graph is the
		* sum of two dataPoints from the combined graphs.
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
