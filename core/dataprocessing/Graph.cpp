#include "Graph.h"


Graph::Graph(dequeue<double> dataPoints, GraphDataType type)
{
	m_GraphDataType = type;
	m_DataPoints = dataPoints;
}

GraphDataType Graph::getType()
{
	return m_GraphDataType;
}

void Graph::moveRight(Graph graph)
{
	foreach(int i in graph.m_DataPoints)
	{
		m_DataPoints.addLast(graph.m_DataPoints);
		m_DataPoints.removeFirst();
	}
}

void Graph::moveLeft(Graph graph)
{
	foreach(int i in graph.m_DataPoints)
	{
		m_DataPoints.addFirst(graph.m_DataPoints);
		m_DataPoints.removeLast();
	}
}
