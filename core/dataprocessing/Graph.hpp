#pragma once

#include <deque>

#include "DataTypes.hpp"

//include QLineSeries//TODO
namespace Graph
{
	class Graph
	{
	private:
		GraphDataType m_graphDataType;		// the graph type of the this object
		std::deque<double> m_dataPoints;	// the points that make up the graph

	public:
		/**
		* Creates a graph wrapping the points given.
		*
		* @param dataPoints the points that make up the graph.
		* @param type the type of graph being created
		*/
		Graph(std::deque<double>& dataPoints, const GraphDataType& type);

		/**
		* returns the type of this graph
		*
		* @return GraphDataType from the graph
		*/
		const GraphDataType getType() const;

		/**
		*
		*
		* @return DataPoints as deque<double>
		*/
		const std::deque<double>& getDataPoints() const;

		/**
		* Appends data points from a graph to the end and removes data points at the front.
		* Therefore moves forward in time.
		*
		* @param graph to appand to the right
		*/
		void moveRight(const Graph& graph);

		/**
		* Appands data points from a graph to the front and removes data points at the end.
		* Therefore moves forward in time.
		*
		* @param graph to appand to the left
		*/
		void moveLeft(const Graph& graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
