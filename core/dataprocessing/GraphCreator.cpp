#include "GraphCreator.h"

namespace Graph
{
	Graph GraphCreator::createGraph(const std::string& threadId,const GraphDataType& type,const timePoint& startTime,const const time_delta& duration)
	{
		std::deque<double> graphData{};
		//m_DataStorage.getData();
		return Graph(graphData, type);
	}
}