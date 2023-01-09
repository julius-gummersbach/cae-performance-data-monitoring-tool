#pragma once

#include <vector>

#include "Graph.h"
#include "Expression.h"


namespace Graph
{
	class GraphManager
	{
	private:
		std::vector<Graph> m_Graphs;
		std::vector<Expression> m_Expressions;
		timePoint m_StartTime;
		timePoint m_EndTime;

	public:
		GraphManager(timePoint startTime, timePoint endtime);//TODO
		void addGraph(Expression expression);
		//void move(delta : TimeSpan);//TODO Time
		//void changeInterval(SYSTEMTIME startTime,SYSTEMTIME endtime);//TODO
		//QChart getChart();//TODO

	};
}
