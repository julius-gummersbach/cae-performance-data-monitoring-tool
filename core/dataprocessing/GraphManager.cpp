#include <unordered_map>
#include <memory>

#include "Graph.hpp"
#include "GraphManager.hpp"

namespace DataProcessing 
{

	// TODO
	GraphManager::GraphManager(const time_point& startTime, const time_delta& duration) : 
		m_startTime{ startTime },
		m_duration{ duration },
		m_graphs{}
	{ }

	void GraphManager::addGraph(const shared_ptr<Expression>& expression)
	{
		m_graphs.emplace(
			expression, 
			expression->getGraph(m_startTime, m_duration));
	}

	void GraphManager::move(const time_delta& delta) {
		time_point intervalStart{ m_startTime + m_duration };

		for (auto& elem : m_graphs) {
			auto graph = elem.first->getGraph(intervalStart, delta);
			elem.second->moveRight(*graph);
		}
	}
	void GraphManager::changeInterval(const time_point& start, const time_delta& duration) {
		m_startTime = start;
		m_duration = duration;

		for (auto& elem : m_graphs) {
			auto graph = elem.first->getGraph(start, duration);
			elem.second.swap(graph);
		}
	}
	//QChart getChart();//TODO
}