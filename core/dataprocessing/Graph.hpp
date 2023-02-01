#pragma once

#include "DataTypes.hpp"

//include QLineSeries//TODO
namespace CAEMonitoringTool::DataProcessing 
{
	class Graph
	{
	private:
		std::vector<std::pair<int, double>>	m_dataPoints;// the points that make up the graph
		std::string m_svgPath;
		//ImageCreator m_imageCreator

	public:
		/**
		* Creates a graph wrapping the points given.
		*
		* @param dataPoints the points that make up the graph.
		* @param type the type of graph being created
		*/
		Graph(const std::vector<std::pair<int, double>>& dataPoints);

		Graph(const Graph& leftGraph,const Graph& rightGraph, callback_function operationFunction);
			
		std::string getImage();
	};
}
