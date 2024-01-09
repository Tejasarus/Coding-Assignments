CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)
Project(test)
ADD_SUBDIRECTORY(googletest)
ADD_SUBDIRECTORY(cpr)
ADD_EXECUTABLE(calendar_application main.cpp Weather.cpp Displayers.cpp)
ADD_EXECUTABLE(test test2.cpp Weather.cpp Displayers.cpp)


TARGET_LINK_LIBRARIES(calendar_application cpr)
TARGET_LINK_LIBRARIES(test gtest cpr)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
