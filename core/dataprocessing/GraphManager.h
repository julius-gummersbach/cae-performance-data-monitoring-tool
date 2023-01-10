#pragma once

#include <vector>
#include <memory>

#include "Graph.h"
#include "Expression.h"


namespace Graph
{
	using std::shared_ptr;

	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<Expression>, shared_ptr<Graph>> m_Graphs;

		timePoint m_StartTime;
		timePoint m_EndTime;

	public:
		GraphManager(const timePoint& startTime, const timePoint& endtime);//TODO
		void addGraph(shared_ptr<Expression> expression);

		//void move(delta : TimeSpan);//TODO Time
		//void changeInterval(SYSTEMTIME startTime,SYSTEMTIME endtime);//TODO
		//QChart getChart();//TODO

	};
}
