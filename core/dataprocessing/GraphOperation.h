#pragma once
#include "Graph.h"

namespace Graph
{
	virtual class GraphOperation
	{
	private:
		Graph evaluate(Graph graph1, Graph graph2)=0;
	private:
		bool checkTypeCompability(GraphDataType graph1, GraphDataType graph2)=0;
	};
}
