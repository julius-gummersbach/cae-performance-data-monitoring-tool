#pragma once

#include "Expression.hpp"
#include "GraphCreator.hpp"

namespace Graph
{
	class AtomicExpression
	{
	private:
		string m_ThreadID;
		GraphDataType m_type;
		GraphCreator m_Creator;

	public:
		/**
		* Creates an Atomic Expression representing a single series of data
		*
		* @param threadId the ID identifying the thread represented
		* @param type the attribute of the Thread beeing represented
		* @param creator the GraphCreator creating the graph from the data store
		*/
		AtomicExpression(string threadID, GraphDataType type, GraphCreator creator);

		/**
		* Differs from the Base class as it creates the Graph from the Data store using the defined GraphCreator
		*
		* @param startTime inclusive, the first point in time to be included in the graph
		* @param duration the amount of time the graph covers, startTime + duration is the first point after the calculated Graph.
		* @return the created Graph
		*/
		shared_ptr<Graph> getGraph(timePoint startTime, time_delta duration) const;
	};
}