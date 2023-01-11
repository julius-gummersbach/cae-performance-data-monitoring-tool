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
		* Creates a CalculatedExpression combining the given two expressions via the given operation.
		*
		* @param lhs left hand side of the calculation
		* @param rhs right hand side of the calculation
		* @param operation the operation combining the two expressions
		*/
		ComposedExpression(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs, shared_ptr<GraphOperation> operation);

		/**
		* Differs from the base calss as it calculates all points from the internally held expressions and operation.
		* The calculation happens inside the GraphOperation object held.
		* 
		* @param startTime inclusive, the first point in time to be included
		* @param duration the amount of time the graph covers, startTime + duration is the first point after the calculated graph.
		* @return the calculated graph
		*/
		shared_ptr<Graph> getGraph(time_point startTime, time_delta duration) const;
	};
}