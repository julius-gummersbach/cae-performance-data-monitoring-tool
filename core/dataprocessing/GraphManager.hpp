#pragma once

#include <vector>
#include <memory>

#include "Graph.hpp"
#include "Expressions/Expression.hpp"


namespace Graph
{
	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<Expression>, shared_ptr<Graph>> m_graphs;

		time_point m_startTime;
		time_delta m_duration;

	public:
		/**
		* @param startTime inclusive, the first point in time to be included
		* @param duration for the time interval
		*/
		GraphManager(const time_point& startTime, const time_delta& duration);

		/**
		* Adds a Graph to the Graphlist.
		*
		* @param expression which contains all information for the Graph
		*/
		void addGraph(const shared_ptr<Expression>& expression);

		/**
		* Changes the start of the time interval for all Graphs.
		*
		* @param delta to move the time interval by
		*/
		void move(const time_delta& delta);

		/**
		* Changes the start and the duration of the time interval for all Graphs.
		*
		* @param startTime
		* @param duration
		*/
		void changeInterval(const time_point& startTime, const time_delta& duration);
		//QChart getChart();
	};
}
