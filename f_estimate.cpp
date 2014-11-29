/*
 * f_estimate.cpp
 *
 *  Created on: 29-Nov-2014
 *      Author: niladriisl
 */

#include </usr/include/eigen3/Eigen/LU>
#include </usr/include/eigen3/Eigen/SVD>
#include </usr/include/eigen3/Eigen/Core>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <iostream>
#include "gaussPdf.h"
#include <math.h>

using namespace Eigen;

long double* f_estimate(const VectorXf input, const MatrixXf Mean,const MatrixXf Sigma, const VectorXf Priors)
{


//	VectorXf input(2);
//	input << 0.5, 0.2;

//	VectorXf mean(2), mean_tmp(4);
//	MatrixXf sigma(2,2);
//
//
//    mean_tmp = Mean.col(0);
//    mean << mean_tmp(0), mean_tmp(1);
//    sigma = Sigma.block(0,0,2,2);

//    long double a = gausspdf(input, mean,sigma);

	MatrixXf input_mean_matrix(2, 6); //   input  position(xi) mean vector for 6 gaussians
	MatrixXf out_mean_matrix(2, 6); //   input velocity(xi dot) mean vector for 6 gaussians
	MatrixXf Sigma_input(12, 2); //  extracted  sigma for input
	MatrixXf Sigma_output_input(12, 2); //   extracted sigma sigmadot for input
	MatrixXf Inverse_Sigma_input(12, 2); // inverse of the sigma matrix taking 6, 2x2 matrix
	VectorXf p(6); //probability of input for 6 components
	VectorXf h(6); // h value in the linear regression equation
	MatrixXf A_matrix(12, 2); // 'A' matrix in the linear regression equation
	MatrixXf B_matrix(2, 6); // 'B' matrix in the linear regression equation
	VectorXf output(2, 1); // output 'xi dot' of regression equation





	int i, j = 0, t, k, m = 0;
	float f = 0; // denominator value of h(k)


	input_mean_matrix = Mean.block(0, 0, 2, 6);
	out_mean_matrix   = Mean.block(2, 0, 2, 6);

	//

	for (i = 0; i < 6; i++) {
		Sigma_input.block(2 * i, 0, 2, 2) = Sigma.block(4 * i, 0, 2, 2);
	}


	//
	for (i = 0; i < 6; i++) {
		Sigma_output_input.block(2 * i, 0, 2, 2) = Sigma.block(4 * i + 2, 0, 2, 2);
	}

    //

	for (i = 0; i <= 10; i = i + 2) //inverse
			{
		Inverse_Sigma_input.block(i, 0, 2, 2) = Sigma_input.block(i, 0, 2, 2).inverse();
	}

	//


	long double prob_input = 0;

	//float prob_input = input_probability(input,Mean1,Sigma1);
	for (k = 0; k < 6; k++) {
		long double prob_input_tmp = gausspdf(input, input_mean_matrix.col(k),
				Sigma_input.block(2 * k, 0, 2, 2));
		long double tmp_Pk = Priors(k) * prob_input_tmp;
		p(k) = tmp_Pk;
		prob_input = prob_input + tmp_Pk;

	}



	for (k = 0; k < 6; k++) {
		long double h_k = p(k) / prob_input;
		h(k) = h_k;
	}

	for (k = 0; k <= 10; k = k + 2) {
		A_matrix.block(k, 0, 2, 2) = Sigma_output_input.block(k, 0, 2, 2) * Inverse_Sigma_input.block(k, 0, 2, 2);
	}

	for (k = 0; k < 6; k++) {
		B_matrix.col(k) = out_mean_matrix.col(k) - A_matrix.block(2 * k, 0, 2, 2) * input_mean_matrix.col(k);
	}

	output << 0, 0;

	for (k = 0; k < 6; k++) {
		output = output + h(k) * (A_matrix.block(2 * k, 0, 2, 2) * input + B_matrix.col(k));

	}




	long double output_array[2];
	output_array[0] = output(0);
	output_array[1] = output(1);
//	std::cout << "correycgjc" << std::endl;


//	std::cout << "from inside   " << output_array[0] << std::endl;

	return output_array;
}
