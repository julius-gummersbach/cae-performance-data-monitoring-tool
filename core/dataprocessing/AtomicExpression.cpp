
#include "AtomicExpression.hpp"

namespace Graph
{
	AtomicExpression::AtomicExpression(string threadID, GraphDataType type, GraphCreator creator) :
		m_ThreadID{ threadID },
		m_type{ type },
		m_Creator{ creator }
	{}

	shared_ptr<Graph> AtomicExpression::getGraph(timePoint start, time_delta stop)
	{
		return m_Creator.createGraph(m_ThreadID, m_type, start, stop);
	}
}