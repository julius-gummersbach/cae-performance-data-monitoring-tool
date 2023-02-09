#pragma once
#include "GraphOperation.hpp"


namespace CAEMonitoringTool::DataProcessing
{
	class GraphAddition :GraphOperation
	{
	public:
		/**
		* Combines two Graphs mathematically.
		* Where each point from the combined graph is the
		* difference of two dataPoints from the combined graphs.
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
		* @return whether or not the types are equal
		*/
		bool checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType);
	};
}