#pragma once

#include <memory>

#include "Graph.hpp"

namespace Graph
{
	class Expression
	{
	public:
		/**
		* Calculates the Graph in the given interval
		*
		* @param startTime inclusive, the first point in time to be included
		* @param duration for the time interval
		* 
		*/
		virtual std::shared_ptr<Graph> getGraph(const timePoint& startTime, const time_delta& duration) = 0;
	};
}
