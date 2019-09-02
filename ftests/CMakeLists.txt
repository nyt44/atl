file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_library(py_atl SHARED ${SOURCE_FILES})
target_link_libraries(py_atl atl_client
                             python3.6m
                             boost_python
                             boost_system)

target_include_directories(py_atl PRIVATE /usr/include/python3.6m)
