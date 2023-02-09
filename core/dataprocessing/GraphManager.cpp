#include <unordered_map>

#include "GraphManager.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	double addition(double value1, double value2)
	{
		return value1 + value2;
	}
	double subtraction(double value1, double value2)
	{
		return value1 - value2;
	}

	double multiplication(double value1, double value2)
	{
		return value1 * value2;
	}

	double division(double value1, double value2)
	{
		return value1 / value2;
	}

	GraphManager::GraphManager()
	{
		m_operations.insert_or_assign("+", &addition);
		m_operations.insert_or_assign("-", &subtraction);
		m_operations.insert_or_assign("*", &multiplication);
		m_operations.insert_or_assign("/", &division);
	}

	void GraphManager::addGraphFromPoints(const json& jsonObject)
	{
		auto jsonIter = jsonObject.at("graph").begin();//TODO funktioniert das mit iterator?
		auto jsonEnd = jsonObject.at("graph").end();
		std::string threadId = jsonObject.at("tid");
		std::vector< std::pair<int, double>> dataPoints{};

		while (jsonIter != jsonEnd)
		{
			dataPoints.push_back(std::pair<int, double>{jsonIter->at("x"), jsonIter->at("y")});
			++jsonIter;
		}
		std::pair<std::string, shared_ptr<Graph>> Point{ jsonObject.at("tid"),std::make_shared<Graph>(Graph(dataPoints,threadId)) };
		m_graphs.insert(Point);
	}

	void GraphManager::addGraphfromCombination(const json& jsonObject)
	{
		std::string threadId = jsonObject.at("resultingGraphName");
		Graph leftGraph = *m_graphs.at(jsonObject.at("lhs")).get();
		Graph rightGraph = *m_graphs.at(jsonObject.at("rhs")).get();
		operationFunction operation = m_operations.at(jsonObject.at("operation"));
		shared_ptr<Graph> composedGraph = std::make_shared<Graph>(leftGraph, rightGraph, operation, threadId);
		std::pair<std::string, shared_ptr<Graph>> graphTupel{ threadId, composedGraph };
		m_graphs.insert(graphTupel);
	}

	std::string GraphManager::getImage(const std::string& threadID)
	{
		return m_graphs.at(threadID).get()->getImage();
	}

	std::string GraphManager::getImage(const std::string& threadID)
	{
		return m_graphs.at(std::make_shared<string>(threadID)).get()->getImage();
	}

}