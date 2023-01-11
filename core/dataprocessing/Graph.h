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
		*
		* @param dataPoints
		*/
		Graph(std::deque<double>& dataPoints,const GraphDataType& type);

		/**
		* @return GraphDataType from the Graph
		*/
		GraphDataType getType();

		/**
		* @return DataPoints as deque<double>
		*/
		std::deque<double> getDataPoints();

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
