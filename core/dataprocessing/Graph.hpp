#pragma once

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
		/**
		* Creates a graph wrapping the points given.
		* 
		* @param dataPoints the points the graph is supposed to contain
		* @param type the type of Graph being created
		*/
		Graph(std::deque<double>& dataPoints,const GraphDataType& type);

		/**
		* returns the type of this Graph
		* 
		* @return GraphDataType from the Graph
		*/
		const GraphDataType getType() const;

		/**
		* 
		* 
		* @return DataPoints as deque<double>
		*/
		const std::deque<double>& getDataPoints() const;

		/**
		* Appands DataPoints from a Graph to the End and removes dataPoints at the Front.
		* Therefore moves forward in time.
		*
		* @param graph to appand to the Right
		*/
		void moveRight(const Graph& graph);

		/**
		* Appands DataPoints from a Graph to the Front and removes dataPoints at the End.
		* Therefore moves forward in time.
		*
		* @param graph to appand to the Left
		*/
		void moveLeft(const Graph& graph);
		//GLineSeries getAsQLineSeries();//TODO

	};
}
