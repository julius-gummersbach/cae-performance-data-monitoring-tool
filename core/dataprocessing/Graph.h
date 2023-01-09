#pragma once

#include <chrono>

namespace Graph
{
	using timePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	enum GraphDataType {};

	class Graph
	{
		enum GraphDataType {};
	private:
		GraphDataType m_GraphDataType;
		double m_DataPoints[];

	public:
		Graph(double dataPoints[], GraphDataType type);
		GraphDataType getType();
		void appendRight(Graph graph);
		void appendLeft(Graph graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
