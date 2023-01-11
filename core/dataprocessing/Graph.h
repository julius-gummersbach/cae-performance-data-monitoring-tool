#pragma once

#include <chrono>
#include <deque>

#include "DataTypes.hpp"

//include QLineSeries//TODO
namespace Graph
{
	class Graph
	{
	private:
		GraphDataType m_GraphDataType;
		std::deque<double> m_DataPoints;

	public:
		Graph(std::deque<double>& dataPoints,const GraphDataType& type);
		GraphDataType getType();
		std::deque<double> getDataPoints();
		void moveRight(const Graph& graph);
		void moveLeft(const Graph& graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
