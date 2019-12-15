file(GLOB SOURCE_FILES "*.pb.h" "*.pb.cc")

add_library(messages SHARED ${SOURCE_FILES})
target_link_libraries(messages protobuf)

target_include_directories(messages PUBLIC .)
