# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# cs225_sources at lib/CMakeLists.txt:12 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/cs225/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/cs225/HSLAPixel.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/cs225/PNG.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/lodepng/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/lodepng/lodepng.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/lodepng/*.h")
set(OLD_GLOB
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/lib/lodepng/lodepng.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/Animation.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/FloodFilledImage.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/Point.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/colorPicker/GradientColorPicker.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/colorPicker/GridColorPicker.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/colorPicker/MyColorPicker.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/colorPicker/RainbowColorPicker.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/colorPicker/SolidColorPicker.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/imageTraversal/BFS.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/imageTraversal/DFS.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/src/imageTraversal/ImageTraversal.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:148 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/tests/tests-part1-BFS-DFS.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/tests/tests_part1-4x4.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/tests/tests_part1-8x4.cpp"
  "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/tests/tests_part2.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/terrypm2/release-f22/mp_traversals/build/CMakeFiles/cmake.verify_globs")
endif()
