#pragma once

#include <chrono>
#include <string>

#include "Graph.hpp"

namespace CAEMonitoringTool
{
	namespace DataProcessing
	{
		class GraphCreator
		{
		private:
			//m_datastorage//TODO
		public:
			/**
			* Gets the data from the datastorage and creates a graph
			*
			* @param threadId to identify a thread
			* @param type of the data stored
			* @param startTime inclusive, the first point in time to be included
			* @param endtime exclusive, the first point in time to not be included
			* @return created graph
			*/
			Graph createGraph(const std::string& threadId, const GraphDataType& type, const time_point& startTime, const time_delta& duration) const;
		};
	}
}
