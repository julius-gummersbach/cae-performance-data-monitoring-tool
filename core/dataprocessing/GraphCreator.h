#pragma once
#include <Minwinbase.h>
#include <string>
#include "Graph.h"

namespace Graph
{
	class GraphCreator
	{

	private:
		//m_Datastorage//TODO
	public:
		Graph createGraph(std::string threadId, GraphDataType type, SYSTEMTIME startTime, SYSTEMTIME endtime);//TODO
	};
}
