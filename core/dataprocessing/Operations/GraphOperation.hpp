#pragma once
#include <queue>
#include <stdexcept>

#include "../Graph.hpp"

namespace DataProcessing
{
	class GraphOperation
	{
	public:
		/**
		* Combines two graphs mathematically
		*
		* @param first graph
		* @param second graph
		* @return the combined graph
		*/
		virtual Graph evaluate(const Graph& firstGraph, const Graph& secondGraph) const = 0;

	private:
		/**
		* Checks if the two types are compatible
		*
		* @param first GraphDataType
		* @param second GraphDataType
		* @return whether or not the types are compatible
		*/
		virtual bool checkTypeCompatibility(const GraphDataType& firstGraphDataType, const GraphDataType& secondGraphDataType) const = 0;
	};
}
