#include "Graph.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	Graph::Graph(const std::vector<std::pair<int, double>>& dataPoints, const std::string& threadId) : m_dataPoints{ dataPoints }, m_threadId{ threadId }
	{}

	Graph::Graph(const Graph& leftGraph, const Graph& rightGraph, const std::string& threadId, operationFunction operation) : m_threadId{ threadId }
	{
		std::vector<std::pair<int, double>>	newDataPoints{};

		auto leftIter = leftGraph.m_dataPoints.begin();
		auto leftEnd = leftGraph.m_dataPoints.end();
		auto rightIter = rightGraph.m_dataPoints.begin();

		while (leftIter != leftEnd)
		{
			newDataPoints.push_back(std::pair<int, double>{leftIter->first, operation(leftIter->second, rightIter->second)});
			++leftIter;
			++rightIter;
		}
		m_dataPoints = newDataPoints;
	}

	const std::string& Graph::getImage()
	{
		if (m_svgPath.empty())
		{
                        //vector<pair<int,double>> exampleData2{};
                        //std::srand(9822);
                        //for(int i = 0; i< 9; i++){      //Minimum 9, 8 leads to empty file (why exactly?)
                        //  exampleData2.push_back(std::make_pair(i,std::rand()));
                        //}
                        //for(int i = 0; i < m_dataPoints.size(); ++i){
                        //  exampleData2.push_back(std::make_pair(m_dataPoints[i].first, m_dataPoints[i].second));
                        //}

                        //exampleData2 = m_dataPoints;
                        //m_svgPath = CAEMonitoringTool::DataProcessing::ImageGenerator::generateImage(exampleData2,"testi");

                        //m_svgPath = CAEMonitoringTool::DataProcessing::ImageGenerator::generateImage(m_dataPoints, m_threadId);

			m_svgPath = ImageGenerator::generateImage(m_dataPoints, m_threadId);
		}
		return m_svgPath;
	}
}