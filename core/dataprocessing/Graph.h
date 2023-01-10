#pragma once
#include <chrono>
#include <dequeue>
//include QLineSeries//TODO
namespace Graph
{
	using timePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	enum GraphDataType {};

	class Graph
	{
		enum GraphDataType {};
	private:
		GraphDataType m_GraphDataType;
		dequeue<double> m_DataPoints;

	public:
		Graph(dequeue<double> dataPoints, GraphDataType type);
		GraphDataType getType();
		void moveRight(Graph graph);
		void moveLeft(Graph graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
