# Path definitions.
set(lib_dir ${CMAKE_CURRENT_SOURCE_DIR})

# Add lodepng library.
set(lodepng_dir ${lib_dir}/lodepng)
file(GLOB_RECURSE lodepng_sources CONFIGURE_DEPENDS ${lodepng_dir}/*.h ${lodepng_dir}/*.cpp)
add_library(lodepng ${lodepng_sources})
set_target_properties(lodepng PROPERTIES LINKER_LANGUAGE CXX)

# Add cs225 library.
set(cs225_dir ${lib_dir}/cs225)
file(GLOB_RECURSE cs225_sources CONFIGURE_DEPENDS ${cs225_dir}/*.cpp)
add_library(cs225 ${cs225_sources})
target_include_directories(cs225 PRIVATE ${lib_dir})
target_link_libraries(cs225 PRIVATE lodepng)

# Add nim_graph library.
set(nim_graph_dir ${lib_dir}/nim_graph)
file(GLOB_RECURSE nim_graph_sources CONFIGURE_DEPENDS ${nim_graph_dir}/*.cpp)
add_library(nim_graph ${nim_graph_sources})
target_include_directories(nim_graph PRIVATE ${lib_dir})
target_link_libraries(nim_graph PRIVATE cs225 lodepng)

# Add overall libs library.
add_library(libs INTERFACE)
target_include_directories(libs INTERFACE ${lib_dir})
target_link_libraries(libs INTERFACE cs225 nim_graph)