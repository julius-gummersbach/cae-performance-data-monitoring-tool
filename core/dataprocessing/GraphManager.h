#pragma once
#include <vector>
//#include <Minwinbase.h>
#include "Graph.h"
#include "Expression.h"
//#include QLineSeries//TODO


namespace Graph
{
	class GraphManager
	{
	private:
		std::vector<Graph> m_Graphs;
		std::vector<Expression> m_Expressions;
		//SYSTEMTIME m_StartTime;
		//SYSTEMTIME m_Endtime;

	public:
		//GraphManager(SYSTEMTIME startTime,SYSTEMTIME endtime);//TODO
		void addGraph(Expression expression);
		//void move(delta : TimeSpan);//TODO Time
		//void changeInterval(SYSTEMTIME startTime,SYSTEMTIME endtime);//TODO
		//QChart getChart();//TODO

	};
}
