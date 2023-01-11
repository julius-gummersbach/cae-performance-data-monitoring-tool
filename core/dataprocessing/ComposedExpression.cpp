#include "ComposedExpression.hpp"

namespace Graph {
	ComposedExpression::ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation) :
		m_LeftExpr{ lhs },
		m_RightExpr{ rhs },
		m_Operation{ operation }
	{}


	shared_ptr<Graph> ComposedExpression::getGraph(timePoint strat, time_delta duration) {
		auto lhs = m_LeftExpr->getGraph(strat, duration);
		auto rhs = m_RightExpr->getGraph(strat, duration);
		return std::make_shared<Graph>(m_Operation->evaluate(*lhs, *rhs));
	}
}
