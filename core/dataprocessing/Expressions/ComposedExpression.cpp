#include "ComposedExpression.hpp"

namespace DataProcessing {
	ComposedExpression::ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation) :
		m_leftExpr{ lhs },
		m_rightExpr{ rhs },
		m_operation{ operation }
	{}


	shared_ptr<Graph> ComposedExpression::getGraph(time_point start, time_delta duration) const 
	{
		auto lhs = m_leftExpr->getGraph(start, duration);
		auto rhs = m_rightExpr->getGraph(start, duration);
		return std::make_shared<Graph>(m_operation->evaluate(*lhs, *rhs));
	}
}
