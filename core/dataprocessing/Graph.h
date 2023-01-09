#pragma once
//include QLineSeries//TODO
namespace Graph
{
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
