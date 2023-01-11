#include "GraphCreator.hpp"

namespace Graph
{
	Graph GraphCreator::createGraph(const std::string& threadId,const GraphDataType& type,const time_point& startTime,const time_delta& duration) const
	{
		std::deque<double> graphData{};
		//m_dataStorage.getData();
		return Graph(graphData, type);
	}
}