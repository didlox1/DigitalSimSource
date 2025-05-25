# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DigitalSim_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DigitalSim_autogen.dir\\ParseCache.txt"
  "DigitalSim_autogen"
  )
endif()
