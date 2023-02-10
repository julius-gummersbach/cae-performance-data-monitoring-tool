//
// Created by CAE-DUALSTUDIS on 01.02.2023.
//

#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP

#include "string"
#include "vector"
#include "PPlot.h"
using namespace SVGChart;
using std::pair;

namespace CAEMonitoringTool::DataProcessing {
	class ImageGenerator {
    private:
        static void plotIt(PPlot& ioPPlot, const vector<pair<int, double>>& points);
	public:
		static std::string generateImage(const std::vector <std::pair<int, double>>& points, const std::string& threadId);
	};
}


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP
