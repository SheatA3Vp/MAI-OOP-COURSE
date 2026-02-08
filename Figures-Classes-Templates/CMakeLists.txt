cmake_minimum_required(VERSION 3.10)
project(Lab03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)


add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME}_exe PRIVATE include/)
target_include_directories(${CMAKE_PROJECT_NAME}_exe PRIVATE include/)   

# Добавление тестов
enable_testing()

add_executable(tests tests/tests.cpp)
target_link_libraries(tests gtest_main)
target_include_directories(tests PRIVATE include/)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)   