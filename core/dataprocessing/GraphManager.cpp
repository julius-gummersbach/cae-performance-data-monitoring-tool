#include <unordered_map>

#include "GraphManager.hpp"

namespace CAEMonitoringTool::DataProcessing
{
	double Addition(double value1, double value2)
	{
		return value1 + value2;
	}
	double Subtraction(double value1, double value2)
	{
		return value1 - value2;
	}

	double Multiplication(double value1, double value2)
	{
		return value1 * value2;
	}

	double Division(double value1, double value2)
	{
		return value1 / value2;
	}

	GraphManager::GraphManager()
	{
		m_operations.insert_or_assign(std::make_shared<string>("+"), &Addition);
		m_operations.insert_or_assign(std::make_shared<string>("-"), &Subtraction);
		m_operations.insert_or_assign(std::make_shared<string>("*"), &Multiplication);
		m_operations.insert_or_assign(std::make_shared<string>("/"), &Division);
	}

	void GraphManager::addGraphFromPoints(const json& jsonStr)
	{
		auto jsonIter = jsonStr.at("graph").begin();//TODO funktioniert das mit iterator?
		auto jsonEnd = jsonStr.at("graph").end();
		std::vector< std::pair<int, double>> dataPoints{};

		while (jsonIter != jsonEnd)
		{
			dataPoints.push_back(std::pair<int, double>{jsonIter->at("x"), jsonIter->at("y")});
			++jsonIter;
		}
		std::pair<shared_ptr<std::string>, shared_ptr<Graph>> Point{ std::make_shared<string>(jsonStr.at("tid")),std::make_shared<Graph>(dataPoints) };
		m_graphs.insert(Point);
	}

	void GraphManager::addGraphfromCombination(std::string jsonStr)
	{
		//m_graphs.insert(makeshared<string>("thread"), Graph{ dataPoints1, dataPoints2, m_operations[std::make_shared<string>("+")]});
	}

}