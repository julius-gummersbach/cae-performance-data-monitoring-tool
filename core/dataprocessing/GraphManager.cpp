#include <unordered_map>
#include <memory>

#include "Graph.hpp"
#include "GraphManager.hpp"

namespace Graph 
{

	// TODO
	GraphManager::GraphManager(const time_point& startTime, const time_delta& duration) : 
		m_StartTime{ startTime },
		m_Duration{ duration },
		m_Graphs{}
	{ }

	void GraphManager::addGraph(const shared_ptr<Expression>& expression)
	{
		m_Graphs.emplace(
			expression, 
			expression->getGraph(m_StartTime, m_Duration));
	}

	void GraphManager::move(const time_delta& delta) {
		time_point intervalStart{ m_StartTime + m_Duration };

		for (auto& elem : m_Graphs) {
			auto graph = elem.first->getGraph(intervalStart, delta);
			elem.second->moveRight(*graph);
		}
	}
	void GraphManager::changeInterval(const time_point& start, const time_delta& duration) {
		m_StartTime = start;
		m_Duration = duration;

		for (auto& elem : m_Graphs) {
			auto graph = elem.first->getGraph(start, duration);
			elem.second.swap(graph);
		}
	}
	//QChart getChart();//TODO
}