cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Dynamic_Imitation)


find_library(EIGEN_LIB eigen $ENV{EIGEN_LIB_PATH})

set(HEADER_FILES /home/niladriisl/eclipse_workspace/Dynamic_Imitation/load_f_data.hpp)
add_executable (f_cap f_cap.cpp load_f_data.cpp ${HEADER_FILES})
