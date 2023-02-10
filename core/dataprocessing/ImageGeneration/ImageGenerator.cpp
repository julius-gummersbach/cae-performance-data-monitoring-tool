#include "PPlot.h"
#include "SVGPainter.h"
#include <string>
#include "ImageGenerator.hpp"
#include "memory"

using namespace SVGChart;
using std::string;
using std::pair;
using std::vector;
using std::make_unique;

namespace CAEMonitoringTool::DataProcessing {

	void plotIt(PPlot& ioPPlot, const vector<pair<int, double>>& points) {
		ioPPlot.mPlotBackground.mTitle = "Our beautiful graph";
		auto* xValues = new PlotData();
		auto* yValues = new PlotData();
		xValues->push_back(0);
		yValues->push_back(0);
		for (auto pair : points) {
			xValues->push_back(pair.first * 16);
			yValues->push_back(pair.second);
		}
		auto* legend = new LegendData();
		legend->mName = "Our sample data";
		legend->mColor = PColor(41, 105, 242);

		ioPPlot.mPlotDataContainer.AddXYPlot(xValues, yValues, legend);

		ioPPlot.mMargins.mLeft = 90;
		ioPPlot.mMargins.mTop = 50;
		ioPPlot.mMargins.mBottom = 50;
		ioPPlot.mMargins.mRight = 50;

		ioPPlot.mXAxisSetup.mLabel = "Time in Milliseconds";
		ioPPlot.mYAxisSetup.mLabel = "Runtime in Milliseconds";
		ioPPlot.mGridInfo.mYGridOn = true;
	}

	std::string ImageGenerator::generateImage(const std::vector<std::pair<int, double>>& points, const std::string& threadId) {
		string path{ "C:\\Users\\aixtron\\source\\repos\\cae - performance - data - monitoring - tool\\core\\main\\webpage\\img\\generated svg files\\" + threadId };
		PPlot pplot;
		plotIt(pplot, points);
		long width = points.size() * 16;
		SVGPainter painter(width, 450);
		pplot.Draw(painter);
		return painter.writeFile(path);
        //return path;
	}
}
