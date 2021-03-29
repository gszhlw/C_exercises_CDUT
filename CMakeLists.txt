cmake_minimum_required(VERSION 3.16)
project(ravenpersonal C)

set(CMAKE_C_STANDARD 99)

add_executable(ravenpersonal test.c experiment_2_4_1.c cmake-build-debug/random_num.c cmake-build-debug/experiments_2_2_9.c experiments_gallon_liter_trans.c experiment_cm_feet_trans.c)