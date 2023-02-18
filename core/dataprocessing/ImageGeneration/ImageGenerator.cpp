#include "PPlot.h"
#include "SVGPainter.h"
#include <string>
#include "ImageGenerator.hpp"
#include "memory"
#include "fstream"

using namespace SVGChart;
using std::string;
using std::pair;
using std::vector;
using std::make_unique;

namespace CAEMonitoringTool::DataProcessing {

	void ImageGenerator::plotIt(PPlot& ioPPlot, const vector<pair<int, double>>& points) {
		auto* xValues = new PlotData();
		auto* yValues = new PlotData();
		xValues->push_back(0);
		yValues->push_back(0);
		for (auto pair : points) {
			xValues->push_back(pair.first * 16);
			yValues->push_back(pair.second);
                }
		auto *legend = new LegendData();
		legend->mColor = PColor(41, 105, 242);

		ioPPlot.mPlotDataContainer.AddXYPlot(xValues, yValues, legend);

		ioPPlot.mMargins.mLeft = 75;
		ioPPlot.mMargins.mTop = 50;
		ioPPlot.mMargins.mBottom = 140;
		ioPPlot.mMargins.mRight = 50;

		ioPPlot.mXAxisSetup.mLabel = "Time (ms)";
		ioPPlot.mYAxisSetup.mLabel = "Runtime (ms)";
		ioPPlot.mGridInfo.mYGridOn = true;
	}

    std::string ImageGenerator::generateImage(const vector<std::pair<int, double>> &points, const string &threadId) {
        string path{threadId + ".svg" };
        PPlot pplot;
        plotIt(pplot,points);
        long width = points.size() * 16;
        SVGPainter painter(width, 450);
        pplot.Draw(painter);
        painter.writeFile(path);

        std::ifstream inFile(path);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        return buffer.str();
    }
}