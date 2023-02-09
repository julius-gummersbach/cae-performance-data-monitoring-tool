#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP

#include <nlohmann/json.hpp>
#include "../datastore/DataManager.hpp"
#include "GraphManager.hpp"
#include "string"

namespace CAEMonitoringTool::DataProcessing {

	using json = nlohmann::json;

	/**
	 * class to receive the incoming json-data strings from the websocket-connector, parse and redistribute it
	 * to the DataManager and GraphManager
	 */
	class DataParser {

	public:

		/**
		 * documentation, edit me later
		 *
		 * @param object
		 * @param dManager
		 * @param gManager
		 * @return
		 */
		static bool parseThreadInfo(const json& object,
			DataStore::DataManager& dManager,
			GraphManager& gManager);
	};
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP