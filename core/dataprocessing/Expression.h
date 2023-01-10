#pragma once

#include <memory>

#include "Graph.h"

namespace Graph
{
	class Expression
	{
	public:
		virtual std::shared_ptr<Graph> getGraph(timePoint startTime, timePoint endtime) = 0;
	};
}
