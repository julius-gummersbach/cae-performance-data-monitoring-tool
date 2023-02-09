//
// Created by CAE-DUALSTUDIS on 01.02.2023.
//

#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP

#include "string"
#include "vector"


namespace CAEMonitoringTool::DataProcessing {
	class ImageGenerator {
	public:
		static std::string generateImage(const std::vector <std::pair<int, double>>& points, const std::string& threadId);
	};
}


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_IMAGEGENERATOR_HPP
