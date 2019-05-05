project(test)
add_subdirectory(gtest)

include_directories(gtest/include gtest)

add_executable(runTests ../myClient.cpp ../myClient.h ../myServer.cpp ../myServer.h tests.cpp)

target_link_libraries(runTests gtest gtest_main)