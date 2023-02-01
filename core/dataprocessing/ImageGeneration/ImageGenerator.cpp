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

    void plotIt(PPlot &ioPPlot, const vector<pair<int,double>>& points){
        ioPPlot.mPlotBackground.mTitle = "Unser wunderschöner Graph";
        auto *xValues = new PlotData();
        auto *yValues = new PlotData();
        xValues->push_back(0);
        yValues->push_back(0);
        for(auto pair : points){
            xValues->push_back(pair.first * 16);
            yValues->push_back(pair.second);
        }
        auto *legend = new LegendData();
        legend->mName = "Unsere Beispiel-Daten";
        legend->mColor = PColor(100, 100, 200);

        ioPPlot.mPlotDataContainer.AddXYPlot(xValues, yValues, legend);

        ioPPlot.mMargins.mLeft = 90;
        ioPPlot.mMargins.mTop = 50;
        ioPPlot.mMargins.mBottom = 50;
        ioPPlot.mMargins.mRight = 50;

        ioPPlot.mXAxisSetup.mLabel = "Zeit in Millisekunden";
        ioPPlot.mYAxisSetup.mLabel = "Laufzeit in Millisekunden";
        ioPPlot.mGridInfo.mYGridOn = true;
    }

    std::string ImageGenerator::generateImage(const vector<std::pair<int, double>> &points) {
        string path{"test5.svg"};
        PPlot pplot;
        plotIt(pplot,points);
        long width = points.size() * 16;
        SVGPainter painter(width, 450);
        pplot.Draw(painter);
        painter.writeFile(path);
        return path;
    }
}

int main() {
    vector<pair<int, double>> exampleData{{0, 1},{1, 2},{2, 3},{3,2},{4,1},{5,0}};
    vector<pair<int, double>> exampleData2{};

    std::srand(9821);
    for(int i = 0; i < std::rand() + 100; i++){
        exampleData2.push_back(std::make_pair(i,std::rand()));
    }

   CAEMonitoringTool::DataProcessing::ImageGenerator::generateImage(exampleData2);
}