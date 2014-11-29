cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Dynamic_Imitation)


find_library(EIGEN_LIB eigen $ENV{EIGEN_LIB_PATH})

set(HEADER_FILES /home/niladriisl/eclipse_workspace/Dynamic_Imitation/load_f_data.h  /home/niladriisl/eclipse_workspace/Dynamic_Imitation/gaussPdf.h /home/niladriisl/eclipse_workspace/Dynamic_Imitation/f_estimate.h) 
add_executable (main main.cpp load_f_data.cpp f_estimate.cpp gaussPdf.cpp ${HEADER_FILES})
