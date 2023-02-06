#pragma once

/* 
* This file contains all type definitions that are used internally.
* Classes and structs are an exception to this.
*/

#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace CAEMonitoringTool::DataProcessing
{
	using json = nlohmann::json;
	typedef double (*callback_function)(double value1, double value2);
	using std::shared_ptr;
	using std::string;
}