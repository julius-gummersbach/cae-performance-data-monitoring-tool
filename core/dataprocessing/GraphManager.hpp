#pragma once

#include "Graph.hpp"
#include "DataTypes.hpp"
#include "GraphOperation.hpp"


namespace CAEMonitoringTool::DataProcessing
{
	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<std::string>, shared_ptr<Graph>> m_graphs;	// all graphs this object manages
		std::unordered_map<shared_ptr<std::string>, shared_ptr<Graph>> m_operations;


	public:

		/**
		* Adds a graph to the graphlist from the given Points.
		*
		* @param jsonStr which includes Points for a Graph
		*/
		void addGraphFromPoints(std::string jsonStr);

		/**
		* Adds a graph to the graphlist by combining the Graphs 
		* spezified in the json String with the spezified Operation.
		*
		* @param Json String which includes the id of two Graphs and a Operation
		*/
		void addGraphfromCombination(std::string jsonStr);
	};
}
