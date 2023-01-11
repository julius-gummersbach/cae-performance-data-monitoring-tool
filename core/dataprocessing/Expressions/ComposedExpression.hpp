#pragma once

#include "Expression.hpp"
#include "../GraphOperation.hpp"

namespace Graph
{
	class ComposedExpression
	{
		shared_ptr<Expression> m_leftExpr;
		shared_ptr<Expression> m_rightExpr;
		shared_ptr<GraphOperation> m_operation;

	public:
		/**
		* Creates a CalculatedExpression combining the given two Expressions via the given Operation.
		*
		* @param lhs left hand side of the calculation
		* @param rhs right hand side of the calculation
		* @param operation the operation combining the two expressions
		*/
		ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation);

		/**
		* Differs from the Base calss as it calculates all points from the internally held Expressions and Operation.
		* The Calculation happens inside the GraphOperation Object held.
		* 
		* @param startTime inclusive, the first point in time to be included
		* @param duration the amount of time the graph covers, startTime + duration is the first point after the calculated Graph.
		* @return the calculated Graph
		*/
		shared_ptr<Graph> getGraph(time_point startTime, time_delta duration) const;
	};
}