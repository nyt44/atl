file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(tests)

add_library(client SHARED ${SOURCE_FILES})
target_link_libraries(client common)

target_include_directories(client PUBLIC .)
