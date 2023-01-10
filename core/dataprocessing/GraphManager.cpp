#include <unordered_map>
#include <memory>

#include "Graph.h"
#include "GraphManager.h"

namespace Graph 
{

	// TODO
	GraphManager::GraphManager(const timePoint& startTime, const time_delta& duration) : 
		m_StartTime{ startTime }, 
		m_Duration{ duration } 
	{ }

	void GraphManager::addGraph(shared_ptr<Expression> expression)
	{
		m_Graphs.emplace(
			expression, 
			expression->getGraph(m_StartTime, m_StartTime + m_Duration));
	}

	void GraphManager::move(time_delta delta) {
		timePoint intervalStart{ m_StartTime + m_Duration };

		for (auto& elem : m_Graphs) {
			auto graph = elem.first->getGraph(intervalStart, intervalStart + delta);
			elem.second->moveRight(*graph);
		}
	}
	void GraphManager::changeInterval(timePoint start, time_delta end) {
		m_StartTime = start;
		m_Duration = end;

		for (auto& elem : m_Graphs) {
			auto graph = elem.first->getGraph(start, start + end);
			elem.second.swap(graph);
		}
	}
	//QChart getChart();//TODO
}