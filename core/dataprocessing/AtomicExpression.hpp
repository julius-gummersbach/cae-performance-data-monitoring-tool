#pragma once

#include "Expression.hpp"
#include "GraphCreator.h"

namespace Graph
{
	class AtomicExpression
	{
	private:
		string m_ThreadID;
		GraphDataType m_type;
		GraphCreator m_Creator;

	public:
		AtomicExpression(string threadID, GraphDataType type, GraphCreator creator);
		shared_ptr<Graph> getGraph(timePoint startTime, time_delta duration);
	};
}