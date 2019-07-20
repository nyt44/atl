file(GLOB SOURCE_FILES "*.hpp" "*.cpp")

add_subdirectory(client)

add_library(atl_client SHARED ${SOURCE_FILES})
target_link_libraries(atl_client client)
