#pragma once
#include "../Graph.hpp"

namespace Graph
{
	class GraphOperation
	{
	public:
		/**
		* Combines two Graphs mathematically
		* 
		* @param firstGraph 
		* @param secondGraph
		* @return the combined graph
		*/
		virtual Graph evaluate(const Graph& firstGraph,const Graph& secondGraph) = 0;

	private:
		/**
		* Checks if the two types are compatible
		*
		* @param firstGraphDataType
		* @param secondGraphDataType
		* @return whether or not the types are compatible
		*/
		virtual bool checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType) = 0;
	};
}
