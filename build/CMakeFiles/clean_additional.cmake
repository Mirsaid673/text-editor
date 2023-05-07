# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/out_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/out_autogen.dir/ParseCache.txt"
  "out_autogen"
  )
endif()
