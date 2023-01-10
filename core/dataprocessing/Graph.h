#pragma once

#include <chrono>
#include <deque>

//include QLineSeries//TODO
namespace Graph
{
	using timePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	enum GraphDataType {};

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
