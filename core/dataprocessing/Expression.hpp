#pragma once

#include <memory>

#include "Graph.hpp"

namespace Graph
{
	class Expression
	{
	public:
		/**
		* Creates the graph defined by this expression in the given interval.
		*
		* @param startTime inclusive, the first point in time to be included
		* @param duration the amount of time the graph covers, startTime + duration is the first point after the calculated Graph.
		* @return the calculated Graph
		*/
		virtual std::shared_ptr<Graph> getGraph(const timePoint& startTime, const time_delta& duration) const = 0;
	};
}
