add_executable(sender sender.cpp)
target_link_libraries(sender atl_client
                             dbg_trace)

add_executable(receiver receiver.cpp)
target_link_libraries(receiver atl_client
                               dbg_trace)

add_executable(protobuf_client protobuf_client.cpp)
target_link_libraries(protobuf_client atl_client
                                      dbg_trace
                                      messages)

add_executable(protobuf_server protobuf_server.cpp)
target_link_libraries(protobuf_server atl_client
                                        dbg_trace
                                        messages)

add_executable(daemon_terminator daemon_terminator.cpp)
target_link_libraries(daemon_terminator atl_client)
