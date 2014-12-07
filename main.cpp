/*
 * 09-11-2014
 * This is the fun
 */
#include"load_f_data.h"
#include"f_estimate.h"
#include"gradient_V.h"
#include"control_input.h"
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
	MatrixXf Sigma(Config(1) * Config(0), Config(0));
	Sigma = load_obj.sigma_tmp;
	VectorXf Xistar(Config(0) / 2);
	Xistar = load_obj.xistar_tmp; /*!< an Eigen Vector value */
	int size_input = Xistar.rows();


	//read input data from a text file
	MatrixXf input_output_array;
	MatrixXf input_array;
	ifstream file_input_output;
	file_input_output.open(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/input_output.txt");
	input_output_array.resize(88, 4);
	for (int i = 0; i < 88; i++) {
		for (int j = 0; j < 4; j++) {
			file_input_output >> input_output_array(i, j);
		}
	}
	file_input_output.close();
	input_array.resize(88, 2);
	input_array = input_output_array.block(0, 0, 88, 2);
	MatrixXf output_array(88, 2);

	gradient_V gradient_obj;



	for (int i = 0; i < 88; i++) {
		VectorXf input(2);
		input(0) = input_array(i, 0);
		input(1) = input_array(i, 1);
		long double *a = f_estimate(input, Mean, Sigma, Priors, Xistar);



		// apply control input with the estimated f

//		cout << "hi haha " << input << "again hi ha ha" << Xistar << endl;

		Eigen::VectorXf gradient_val = gradient_obj.calculate_gradient(input,
				Xistar);

//		cout << "hi haha " << endl;


		Eigen::VectorXf f_estimate(size_input);

		for (int j = 0; j < size_input; j++) {
			f_estimate(j) = a[j];
		}

		Eigen::VectorXf final_f_estimate;
		final_f_estimate = f_estimate
				+ control_input(input, gradient_val, Xistar, f_estimate, 0.01,
						0.01); // manually setting the value of rho and K

		output_array(i, 0) = final_f_estimate(0);
		output_array(i, 1) = final_f_estimate(1);


//		output_array(i, 0) = a[0];
//		output_array(i, 1) = a[1];

	}

	std::ofstream file_output(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/estimated_output.txt");
	if (file_output.is_open()) {
		file_output << output_array;
	}

	file_output.close();
	std::cout << output_array << std::endl;

	return 0;
}

