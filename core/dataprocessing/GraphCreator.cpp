#include "GraphCreator.h"

namespace Graph
{
	Graph GraphCreator::createGraph(std::string threadId, GraphDataType type, timePoint startTime, timePoint endtime)
	{

		deque<double> graphData;
		//m_DataStorage.getData();
		return new Graph(graphData, type);
	}
}