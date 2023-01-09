PROJECT(CAE_Performance_Data_Monitoring_Tool)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(main)
add_subdirectory(dataprocessing)
add_subdirectory(datastore)

# These directories must not be added to git!
#DEBUG compile targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG build/debug)
#RELEASE compile targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_ RELEASE build/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_ RELEASE build/release)
