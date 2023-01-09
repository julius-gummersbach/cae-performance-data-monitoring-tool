#include "GraphManager.h"

std::vector<Graph> m_Graphs;
std::vector<Expression> m_Expressions;

	GraphManager(SYSTEMTIME startTime, SYSTEMTIME endtime);//TODO
	void addGraph(Expression expression)
	{
		m_Expressions.push_back(expression);
		m_Graphs.push_back(expression.getGraph(startTime, endtime));//TODO);
	}
	//void move(delta : TimeSpan);//TODO Time
	//void changeInterval(start : Time, duration : TimeSpan);//TODO Time
	//QChart getChart();//TODO