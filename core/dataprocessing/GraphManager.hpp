#pragma once

#include <vector>
#include <memory>

#include "Graph.hpp"
#include "Expressions/Expression.hpp"


namespace CAEMonitoringTool::DataProcessing
{
	class GraphManager
	{
	private:
		std::unordered_map<shared_ptr<Expression>, shared_ptr<Graph>> m_graphs;	// all graphs this object manages

		time_point m_startTime;	// a GraphManager manages graphs over a fixed period in time. This is the start of that period
		time_delta m_duration;	// a GraphManager manages graphs over a fixed period in time. This is the duration of that period

	public:
		/**
		* @param startTime inclusive, the first point in time to be included
		* @param duration for the time interval
		*/
		GraphManager(const time_point& startTime, const time_delta& duration);

		/**
		* Adds a graph to the graphlist.
		*
		* @param expression which contains all information for the graph
		*/
		void addGraph(const shared_ptr<Expression>& expression);

		/**
		* Changes the start of the time interval for all graphs.
		*
		* @param delta to move the time interval by
		*/
		void move(const time_delta& delta);

		/**
		* Changes the start and the duration of the time interval for all graphs.
		*
		* @param startTime
		* @param duration
		*/
		void changeInterval(const time_point& startTime, const time_delta& duration);
		//QChart getChart();
	};
}
