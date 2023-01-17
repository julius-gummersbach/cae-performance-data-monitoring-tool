
#include "AtomicExpression.hpp"

namespace DataProcessing
{
	AtomicExpression::AtomicExpression(string threadID, GraphDataType type, GraphCreator creator) :
		m_threadID{ threadID },
		m_type{ type },
		m_creator{ creator }
	{}

	shared_ptr<Graph> AtomicExpression::getGraph(time_point start, time_delta duration) const
	{
		return std::make_shared<Graph>(m_creator.createGraph(m_threadID, m_type, start, duration));
	}
}