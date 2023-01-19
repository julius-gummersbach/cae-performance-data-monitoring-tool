#include "GraphCreator.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	Graph GraphCreator::createGraph(const std::string& threadId, const GraphDataType& type, const time_point& startTime, const time_delta& duration) const
	{
		std::deque<double> graphData{};
		//m_dataStorage.getData();
		return Graph(graphData, type);
	}
}