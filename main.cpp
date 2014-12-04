/*
 * 09-11-2014
 * This is the fun
 */
#include"load_f_data.h"
#include"f_estimate.h"
#include </usr/include/eigen3/Eigen/Core>
#include <iostream>
#include "gaussPdf.h"
#include </usr/include/eigen3/Eigen/LU>
#include </usr/include/eigen3/Eigen/SVD>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <fstream>


using namespace Eigen;
using namespace std;

int main() {



	/*
	 * First initiate the class
	 */
	load_function_data load_obj;

	VectorXi Config(2); // always two arguments
	Config = load_obj.sys_config;


	VectorXf Priors(Config(1));
	Priors = load_obj.priors_tmp; /*!< an Eigen Vector value */



	MatrixXf Mean(Config(0), Config(1));
	Mean = load_obj.mean_tmp;



	MatrixXf Sigma(Config(1)*Config(0), Config(0));
	Sigma = load_obj.sigma_tmp;

	cout << "hi haha " << Sigma << endl;

	VectorXf Xistar(Config(0)/2);
	Xistar = load_obj.xistar_tmp; /*!< an Eigen Vector value */






	//read input data from a text file
	MatrixXf input_output_array;
	MatrixXf input_array;
	// for now we know the number of data points
	ifstream file_input_output;
	file_input_output.open("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/input_output.txt");
	input_output_array.resize(88, 4);
	for (int i = 0; i < 88; i++) {
		for (int j = 0; j < 4; j++) {
			file_input_output >> input_output_array(i, j);
		}
	}
	file_input_output.close();

	input_array.resize(88, 2);
	input_array  = input_output_array.block(0,0,88,2);
	//dummy input
	MatrixXf output_array(88,2);
//	VectorXf input(2);
//	input << 0.5, 0.2;

	for (int i = 0; i < 88; i++) {
		VectorXf input(2);
		input(0) = input_array(i,0);
		input(1) = input_array(i,1);
		long double *a = f_estimate(input, Mean, Sigma, Priors, Xistar);
		output_array(i,0) = a[0];
		output_array(i,1) = a[1];

	}


	std::ofstream file_output("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/estimated_output.txt");
		  if (file_output.is_open())
		    {
			  file_output << output_array    ;
		    }

		  file_output.close();
	std::cout << output_array << std::endl;

	return 0;
}

