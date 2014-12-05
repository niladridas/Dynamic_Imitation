cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(Dynamic_Imitation)


find_library(EIGEN_LIB eigen $ENV{EIGEN_LIB_PATH})

#find_package(Boost COMPONENTS system filesystem REQUIRED)


set(HEADER_FILES /home/niladriisl/eclipse_workspace/Dynamic_Imitation/load_f_data.h  
				/home/niladriisl/eclipse_workspace/Dynamic_Imitation/gaussPdf.h
				 /home/niladriisl/eclipse_workspace/Dynamic_Imitation/f_estimate.h
				 /home/niladriisl/eclipse_workspace/Dynamic_Imitation/gradient_V.h
				 /home/niladriisl/eclipse_workspace/Dynamic_Imitation/control_input.h
				 /home/niladriisl/eclipse_workspace/gnuplot-iostream/gnuplot-iostream.h
				 ) 
add_executable (main main.cpp load_f_data.cpp f_estimate.cpp gaussPdf.cpp gradient_V.cpp control_input.cpp ${HEADER_FILES})
#target_link_libraries( main ${Boost_LIBRARIES} )

