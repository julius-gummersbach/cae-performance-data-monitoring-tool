#pragma once

#include "Expression.hpp"
#include "GraphOperation.h"

namespace Graph
{
	class ComposedExpression
	{
		shared_ptr<Expression> m_LeftExpr;
		shared_ptr<Expression> m_RightExpr;
		shared_ptr<GraphOperation> m_Operation;

	public:
		ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation);
		shared_ptr<Graph> getGraph(timePoint startTime, timePoint endtime);
	};
}