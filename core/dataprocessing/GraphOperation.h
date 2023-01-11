#pragma once
#include "Graph.h"

namespace Graph
{
	class GraphOperation
	{
	public:
		shared_ptr<Graph> evaluate(shared_ptr<Graph> graph1, shared_ptr<Graph> graph2);
		//bool checkTypeCompability(GraphDataType graph1, GraphDataType graph2);//TODO
	};
}
