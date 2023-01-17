#pragma once

/* 
* This file contains all type definitions that are used internally.
* Classes and structs are an exception to this.
*/

#include <chrono>
#include <memory>
#include <string>

namespace Graph
{
	using namespace std::chrono_literals;
	using time_delta = std::chrono::nanoseconds;
	using time_point = std::chrono::time_point<std::chrono::system_clock, time_delta>;
	using std::shared_ptr;
	using std::string;

	enum GraphDataType {
    DATA_SUM_RT,
    INFO_SUM_RT,
    MAX_RT,
    AVG_RT,
    SUM_VS,
    SUM_IS,
    FREQ,
    ITERATIONS,
    OVERRUNS
  };
}