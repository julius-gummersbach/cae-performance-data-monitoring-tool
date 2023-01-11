#pragma once
#include "Graph.hpp"

namespace Graph
{
	class GraphOperation
	{
	public:
		virtual shared_ptr<Graph> evaluate(shared_ptr<Graph> graph1, shared_ptr<Graph> graph2) = 0;
		virtual bool checkTypeCompability(GraphDataType graph1, GraphDataType graph2) = 0;//TODO
	};
}
