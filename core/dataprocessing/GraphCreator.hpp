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
		/**
		* Gets the Data from the Datastorage and creates a Graph
		* 
		* @param threadId to identify a Thread
		* @param type of the Data stored
		* @param startTime inclusive, the first point in time to be included
		* @param endtime exclusive, the first point in time to not be included
		* @return created Graph
		*/
		Graph createGraph(const std::string& threadId,const GraphDataType& type,const timePoint& startTime, const time_delta& duration);
	};
}
