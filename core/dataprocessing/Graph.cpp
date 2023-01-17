#include "Graph.hpp"

namespace DataProcessing {

	Graph::Graph(std::deque<double>& dataPoints, const GraphDataType& type)
	{
		m_graphDataType = type;
		m_dataPoints = std::move(dataPoints);
	}

	const GraphDataType Graph::getType() const
	{
		return m_graphDataType;
	}

	const std::deque<double>& Graph::getDataPoints() const
	{
		return m_dataPoints;
	}

	void Graph::moveRight(const Graph& graph)
	{
		for (auto& p : graph.m_dataPoints)
		{
			m_dataPoints.push_back(p);
			m_dataPoints.pop_front();
		}
	}

	void Graph::moveLeft(const Graph& graph)
	{
		for (auto& p : graph.m_dataPoints)
		{
			m_dataPoints.push_front(p);
			m_dataPoints.pop_back();
		}
	}
}