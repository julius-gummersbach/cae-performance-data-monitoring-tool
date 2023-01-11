#pragma once

#include <memory>

#include "Graph.h"

namespace Graph
{
	virtual class Expression
	{
	public:
		/// <summary>
		/// Calculates the Graph inbetween the two time Points
		/// </summary>
		/// <param name="startTime">inclusive, the first point in time to be included</param>
		/// <param name="endtime">exclusive, the first point in time to not be included</param>
		/// <returns>A shared Pointer to the generated Graph</returns>
		virtual std::shared_ptr<Graph> getGraph(const timePoint& startTime, const time_delta& duration) = 0;
	};
}
