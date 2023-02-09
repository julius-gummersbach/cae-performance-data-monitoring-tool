#pragma once
#include "GraphOperation.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	class GraphDivision :GraphOperation
	{
	public:
		/**
		* Combines two Graphs mathematically.
		* Where each point from the combined graph is the
		* ratio of two dataPoints from the combined graphs.
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
