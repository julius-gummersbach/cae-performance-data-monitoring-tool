#include "Graph.h"

namespace Graph {
	Graph::Graph(std::deque<double>& dataPoints,const GraphDataType& type)
	{
		m_GraphDataType = type;
		m_DataPoints = std::move(dataPoints);
	}

	GraphDataType Graph::getType()
	{
		return m_GraphDataType;
	}

	std::deque<double> Graph::getDataPoints()
	{
		return m_DataPoints;
	}

	void Graph::moveRight(const Graph& graph)
	{
		for(auto& p : graph.m_DataPoints)
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