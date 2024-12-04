cmake_minimum_required(VERSION 3.14)
project(spring-in-cpp-colorpair)

# Add Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



enable_testing()

file(GLOB SOURCES "*.cpp")
add_executable(
  TelCoColorCoder
  ${SOURCES}
)
target_link_libraries(
  TelCoColorCoder
  GTest::gtest_main
  ${GTEST_LIBRARIES}
)

# Check the compiler and add the appropriate flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(TelCoColorCoder PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(TelCoColorCoder PRIVATE /W4 /WX)
endif()

include(GoogleTest)
gtest_discover_tests(TelCoColorCoder)