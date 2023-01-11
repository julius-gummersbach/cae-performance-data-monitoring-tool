#include "ComposedExpression.hpp"

namespace Graph {
	ComposedExpression::ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation) :
		m_leftExpr{ lhs },
		m_rightExpr{ rhs },
		m_operation{ operation }
	{}


	shared_ptr<Graph> ComposedExpression::getGraph(time_point strat, time_delta duration) const 
	{
		auto lhs = m_leftExpr->getGraph(strat, duration);
		auto rhs = m_rightExpr->getGraph(strat, duration);
		return std::make_shared<Graph>(m_operation->evaluate(*lhs, *rhs));
	}
}
