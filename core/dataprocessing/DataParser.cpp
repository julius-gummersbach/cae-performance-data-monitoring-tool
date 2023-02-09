#include "DataParser.hpp"

using json = nlohmann::json;

namespace CAEMonitoringTool::DataProcessing {

	bool DataParser::parseThreadInfo(const std::string& jsonContent,
		DataStore::DataManager& dManager,
		GraphManager& gManager) {

        json object = json::parse(jsonContent);

		std::string id{ object.at("tid") };
		std::string points;
		points.append(R"({ "tid": ")")
			.append(id)
			.append(R"(", "graph" :)")
			.append(object["graph"].dump())
			.append("}");

		gManager.addGraphFromPoints(json::parse(points));

		std::string jsonString{ object.dump() };
		std::string threadInfo = jsonString.substr(0, jsonString.find("graph") - 2)
			.append(jsonString.substr(jsonString.find("iterations") - 2));

		dManager.addData(json::parse(jsonString));

		return object["isDone"];
	}

}