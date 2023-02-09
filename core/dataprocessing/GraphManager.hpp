#pragma once

#include "Graph.hpp"
#include "DataTypes.hpp"


namespace CAEMonitoringTool::DataProcessing
{
	class GraphManager
	{
	private:
		std::unordered_map<std::string, shared_ptr<Graph>> m_graphs;	// all graphs this object manages
		std::unordered_map<std::string, operationFunction> m_operations;


	public:

		GraphManager();

		/**
		* Adds a graph to the graphlist from the given Points.
		*
		* @param jsonStr which includes Points for a Graph
		*/
		void addGraphFromPoints(const json& jsonObject);

		/**
		* Adds a graph to the graphlist by combining the Graphs
		* spezified in the json String with the spezified Operation.
		*
		* @param Json String which includes the id of two Graphs and a Operation
		*/
		void addGraphfromCombination(const json& jsonObject);

		const std::string& getImage(const std::string& threadID);
	};
}
