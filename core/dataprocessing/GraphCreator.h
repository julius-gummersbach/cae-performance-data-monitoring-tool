#pragma once
#include <Minwinbase.h>
#include <string>
#include "Graph.h"

namespace Graph
{
	enum GraphDataType {};

	class GraphCreator
	{

	private:
		//m_Datastorage//TODO
	public:
		Graph createGraph(std::string threadId, GraphDataType type, SYSTEMTIME startTime, SYSTEMTIME endtime);//TODO
	};
}
