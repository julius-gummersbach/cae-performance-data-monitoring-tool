#pragma once

#include "Expression.hpp"
#include "../GraphCreator.hpp"

namespace Graph
{
	class AtomicExpression
	{
	private:
		string m_threadID;
		GraphDataType m_type;
		GraphCreator m_creator;

	public:
		/**
		* Creates an atomic expression representing a single series of data
		*
		* @param threadId the ID identifying the thread represented
		* @param type the attribute of the thread beeing represented
		* @param creator the GraphCreator creating the graph from the data store
		*/
		AtomicExpression(string threadID, GraphDataType type, GraphCreator creator);

		/**
		* Differs from the base class as it creates the graph from the data store using the defined GraphCreator
		*
		* @param startTime inclusive, the first point in time to be included in the graph
		* @param duration the amount of time the graph covers, startTime + duration is the first point after the calculated graph.
		* @return the created graph
		*/
		shared_ptr<Graph> getGraph(time_point startTime, time_delta duration) const;
	};
}