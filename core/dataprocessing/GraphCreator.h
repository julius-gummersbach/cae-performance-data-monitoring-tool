#pragma once

#include <chrono>
#include <string>

#include "Graph.h"

namespace Graph
{
	class GraphCreator
	{

	private:
		//m_Datastorage//TODO
	public:
		Graph createGraph(std::string threadId, GraphDataType type, timePoint startTime, timePoint endtime);//TODO
	};
}
