#include <unordered_map>
#include <memory>

#include "Graph.h"
#include "GraphManager.h"

namespace Graph 
{

	// TODO
	GraphManager::GraphManager(const timePoint& startTime, const timePoint& endtime) { }

	void GraphManager::addGraph(shared_ptr<Expression> expression)
	{
		m_Graphs.emplace(
			expression, 
			expression->getGraph(m_StartTime, m_EndTime));
	}

	//void move(delta : TimeSpan);//TODO Time
	//void changeInterval(start : Time, duration : TimeSpan);//TODO Time
	//QChart getChart();//TODO
}