#pragma once

#include <vector>
#include <memory>

#include "Graph.hpp"
#include "Expression.hpp"


namespace Graph
{
	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<Expression>, shared_ptr<Graph>> m_Graphs;

		timePoint m_StartTime;
		time_delta m_Duration;

	public:
		/**
		* @param startTime inclusive, the first point in time to be included
		* @param duration for the time interval
		*/
		GraphManager(const timePoint& startTime, const time_delta& duration);

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
		void changeInterval(const timePoint& startTime, const time_delta& duration);
		//QChart getChart();
	};
}
