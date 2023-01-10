#include "Graph.h"
#include "GraphManager.h"

namespace Graph {

		std::vector<Graph> m_Graphs;
		std::vector<Expression> m_Expressions;

		// TODO
		GraphManager::GraphManager(timePoint startTime, timePoint endtime) { }

		void GraphManager::addGraph(Expression expression)
		{
			m_Expressions.push_back(expression);
			m_Graphs.push_back(expression.getGraph(m_StartTime, m_EndTime));//TODO);
		}

		//void move(delta : TimeSpan);//TODO Time
		//void changeInterval(start : Time, duration : TimeSpan);//TODO Time
		//QChart getChart();//TODO
}