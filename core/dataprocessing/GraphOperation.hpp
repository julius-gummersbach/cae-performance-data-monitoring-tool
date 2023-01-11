#pragma once
#include "Graph.hpp"

namespace Graph
{
	virtual class GraphOperation
	{
	public:
		shared_ptr<Graph> evaluate(shared_ptr<Graph> graph1, shared_ptr<Graph> graph2);
		//bool checkTypeCompability(GraphDataType graph1, GraphDataType graph2);//TODO
	};
}
