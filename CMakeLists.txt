cmake_minimum_required(VERSION 3.0.0)
project(power-log-serial2 VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(power-log-serial2 main.cpp)

target_include_directories(power-log-serial2 PUBLIC "/Users/richc/src/boost_1_79_0")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
