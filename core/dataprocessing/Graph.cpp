#include "Graph.hpp"

namespace Graph {

	Graph::Graph(std::deque<double>& dataPoints, const GraphDataType& type)
	{
		m_GraphDataType = type;
		m_DataPoints = std::move(dataPoints);
	}

	const GraphDataType Graph::getType() const
	{
		return m_GraphDataType;
	}

	const std::deque<double>& Graph::getDataPoints() const
	{
		return m_DataPoints;
	}

	void Graph::moveRight(const Graph& graph)
	{
		for (auto& p : graph.m_DataPoints)
		{
			m_DataPoints.push_back(p);
			m_DataPoints.pop_front();
		}
	}

	void Graph::moveLeft(const Graph& graph)
	{
		for (auto& p : graph.m_DataPoints)
		{
			m_DataPoints.push_front(p);
			m_DataPoints.pop_back();
		}
	}
}