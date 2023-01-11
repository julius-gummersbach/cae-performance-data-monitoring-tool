#pragma once

#include <vector>
#include <memory>

#include "Graph.h"
#include "Expression.hpp"


namespace Graph
{
	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<Expression>, shared_ptr<Graph>> m_Graphs;

		timePoint m_StartTime;
		time_delta m_Duration;

	public:
		/**
		* Gets the Data from the Datastorage and creates a Graph
		*
		* @param threadId to identify a Thread
		* @param type of the Data stored
		* @param startTime inclusive, the first point in time to be included
		* @param endtime exclusive, the first point in time to not be included
		*/
		GraphManager(const timePoint& startTime, const time_delta& duration);

		void addGraph(const shared_ptr<Expression>& expression);
		void move(const time_delta& delta);
		void changeInterval(const timePoint& startTime, const time_delta& duration);
		//QChart getChart();//TODO
	};
}
