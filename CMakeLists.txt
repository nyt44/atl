cmake_minimum_required(VERSION 3.10)

project(atl)

add_executable(sender sender.cpp)
target_link_libraries(sender -lrt -lpthread)

add_executable(receiver receiver.cpp)
target_link_libraries(receiver -lrt -lpthread)

add_executable(creator creator.cpp)
target_link_libraries(creator -lrt -lpthread)

add_executable(destroyer destroyer.cpp)
target_link_libraries(destroyer -lrt -lpthread)



