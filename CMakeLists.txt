cmake_minimum_required(VERSION 3.10)

project(atl)

#debug options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#warning options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

#C++ standard option
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#CCache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

add_executable(sender sender.cpp)
target_link_libraries(sender -lrt -lpthread)

add_executable(receiver receiver.cpp)
target_link_libraries(receiver -lrt -lpthread)

add_executable(creator creator.cpp)
target_link_libraries(creator -lrt -lpthread)

add_executable(destroyer destroyer.cpp)
target_link_libraries(destroyer -lrt -lpthread)



