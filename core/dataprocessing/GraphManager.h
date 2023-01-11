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
		GraphManager(const timePoint& startTime, const time_delta& duration);

		void addGraph(shared_ptr<Expression> expression);
		void move(time_delta delta);
		void changeInterval(timePoint startTime, time_delta duration);
		//QChart getChart();//TODO
	};
}
