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

	void GraphManager::addGraphFromPoints(std::string jsonStr)
	{
		
		//m_graphs.insert(makeshared<string>("thread"), Graph{ dataPoints });
	}

	void GraphManager::addGraphfromCombination(std::string jsonStr)
	{
		//m_graphs.insert(makeshared<string>("thread"), Graph{ dataPoints1, dataPoints2, m_operations[std::make_shared<string>("+")]});
	}

}