#pragma once
#include "Graph.h"

namespace Graph
{
	virtual class GraphOperation
	{
	private:
		Graph evaluate(const Graph& graph1,const Graph graph2)=0;
	private:
		bool checkTypeCompability(const GraphDataType& graph1, const GraphDataType& graph2)=0;
	};
}
