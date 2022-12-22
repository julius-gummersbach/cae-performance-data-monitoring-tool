PROJECT(CAE_Performance_Data_Monitoring_Tool)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(main)
add_subdirectory(dataprocessing)
add_subdirectory(datastore)

# build destination: /build/<release/debug>. This directory must not be added to git!
