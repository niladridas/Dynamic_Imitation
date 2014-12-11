cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Dynamic_Imitation)

find_library(EIGEN_LIB eigen $ENV{EIGEN_LIB_PATH})
set(HEADER_FILES load_f_data.h gaussPdf.h f_estimate.h gradient_V.h control_input.h ../gnuplot-iostream/gnuplot-iostream.h) 				 
add_executable (main main.cpp load_f_data.cpp f_estimate.cpp gaussPdf.cpp gradient_V.cpp control_input.cpp ${HEADER_FILES})


