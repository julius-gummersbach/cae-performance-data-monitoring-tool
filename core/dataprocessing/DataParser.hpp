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
		 * method to take the incoming data from the websocket as a json string representation, parse it and distribute it
		 * to the datamanager and graphmanager
		 * @param object string representation of a json object of all information of a single thread
		 * @param dManager reference to a datamanager object to add the information of the thread to
		 * @param gManager reference to a graphmanager object to add the information of the thread to
		 * @return boolean if this was the last sent object from the websocket
		 */
		static bool parseThreadInfo(const std::string& jsonContent,
			DataStore::DataManager& dManager,
			GraphManager& gManager);
	};
}
#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_DATAPARSER_HPP