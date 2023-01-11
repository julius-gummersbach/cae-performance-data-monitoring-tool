#pragma once

#include <deque>
#include <vector>

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
		Graph(std::deque<double>& dataPoints, GraphDataType type);
		GraphDataType getType();
		void moveRight(const Graph& graph);
		void moveLeft(const Graph& graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
