#include "ComposedExpression.hpp"

namespace Graph {
	ComposedExpression::ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation) :
		m_LeftExpr{ lhs },
		m_RightExpr{ rhs },
		m_Operation{ operation }
	{}


	shared_ptr<Graph> ComposedExpression::getGraph(timePoint strat, time_delta stop) {
		auto lhs = m_LeftExpr->getGraph(strat, stop);
		auto rhs = m_RightExpr->getGraph(strat, stop);
		return m_Operation->evaluate(lhs, rhs);
	}
}
