#include "PPlot.h"
#include "SVGPainter.h"
#include <string>
#include "ImageGenerator.hpp"
#include "memory"
#include "iostream"

using namespace SVGChart;
using std::string;
using std::pair;
using std::vector;
using std::make_unique;



namespace CAEMonitoringTool::DataProcessing {

    void test(PPlot &ioPPlot) {
        ioPPlot.mPlotBackground.mTitle = "Mein graph XD";
        PlotData *theX1 = new PlotData();
        PlotData *theY1 = new PlotData();

        PlotData *theX2 = new PlotData();
        PlotData *theY2 = new PlotData();

        auto *theX3 = new PlotData();
        auto *theY3 = new PlotData();

        float theFac = 100.0f / (100 * 100 * 100);
        theX1->push_back(0);
        theY1->push_back(0);
        for (int theI = 0; theI <= 10; theI++) {
            theX1->push_back(0.001 * theI);
            theY1->push_back(0.01 + theFac * theI * theI * theI);

            theX2->push_back(0.001 * theI);
            theY2->push_back(0.01 + theFac * theI * theI * theI + 0.02);
        }
        LegendData *theLegend = new LegendData();
        theLegend->mName = "Harold";
        theLegend->mColor = PColor(100, 100, 200);

        LegendData *theLegend2 = new LegendData();
        theLegend2->mName = "Berta";
        theLegend2->mColor = PColor(255, 0, 0);
        //PlotDataSelection *thePlotDataSelection = new PlotDataSelection ();
        //ioPPlot.mPlotDataContainer.AddXYPlot (theX1, theY1, theLegend, 0, thePlotDataSelection);
        ioPPlot.mPlotDataContainer.AddXYPlot(theX1, theY1, theLegend);
        ioPPlot.mPlotDataContainer.AddXYPlot(theX2, theY2, theLegend2);

        ioPPlot.mMargins.mLeft = 90;
        ioPPlot.mMargins.mTop = 50;
        ioPPlot.mMargins.mBottom = 50;
        ioPPlot.mMargins.mRight = 50;
    }


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

        //PlotDataSelection *thePlotDataSelection = new PlotDataSelection ();
        //ioPPlot.mPlotDataContainer.AddXYPlot (theX1, theY1, theLegend, 0, thePlotDataSelection);
        ioPPlot.mPlotDataContainer.AddXYPlot(xValues, yValues, legend);

        ioPPlot.mMargins.mLeft = 90;
        ioPPlot.mMargins.mTop = 50;
        ioPPlot.mMargins.mBottom = 50;
        ioPPlot.mMargins.mRight = 50;
    }

    std::string ImageGenerator::generateImage(const vector<std::pair<int, double>> &points) {
        string path{"test5.svg"};
        PPlot pplot;
        //test(pplot);
        plotIt(pplot,points);
        long width = points.size() * 16;
        std::cout << points.size() << std::endl;
        SVGPainter painter(width, 450); //490, 450
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