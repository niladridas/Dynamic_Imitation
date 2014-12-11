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

 long double* f_estimate(const VectorXf input, const MatrixXf Mean,const MatrixXf Sigma, const VectorXf Priors, const VectorXf Xi_star)
{



	// First calculate dimension of priors
	int dim_priors = Priors.rows(); // priors comes as a rows
	int dim_input = input.rows();


	MatrixXf input_mean_matrix(dim_input, dim_priors); //   input  position(xi) mean vector for 6 gaussians
	MatrixXf out_mean_matrix(dim_input, dim_priors); //
	MatrixXf Sigma_input(dim_input*dim_priors, dim_input); //  extracted  sigma for input
	MatrixXf Sigma_output_input(dim_input*dim_priors, dim_input); //   extracted sigma sigmadot for input
	MatrixXf Inverse_Sigma_input(dim_input*dim_priors, dim_input); // inverse of the sigma matrix taking 6, 2x2 matrix
	VectorXf p(dim_priors); //probability of input for 6 components
	VectorXf h(dim_priors); // h value in the linear regression equation
	MatrixXf A_matrix(dim_input*dim_priors, dim_input); // 'A' matrix in the linear regression equation
	MatrixXf B_matrix(dim_input, dim_priors); // 'B' matrix in the linear regression equation
	VectorXf output(dim_input); // output 'xi dot' of regression equation

	int i, j = 0, t, k, m = 0;
	float f = 0; // denominator value of h(k)


	input_mean_matrix = Mean.block(0, 0, dim_input, dim_priors);
	out_mean_matrix   = Mean.block(dim_input, 0, dim_input, dim_priors);

	//

	for (i = 0; i < dim_priors; i++) {
		Sigma_input.block(dim_input * i, 0, dim_input, dim_input) = Sigma.block(2*dim_input* i, 0, dim_input, dim_input);
	}


	//
	for (i = 0; i < dim_priors; i++) {
		Sigma_output_input.block(dim_input * i, 0, dim_input, dim_input) = Sigma.block(2*dim_input* i + dim_input, 0, dim_input, dim_input);
	}

    //

	for (i = 0; i < dim_input*dim_priors - dim_input ; i = i + dim_input) //inverse
			{
		Inverse_Sigma_input.block(i, 0, dim_input, dim_input) = Sigma_input.block(i, 0, dim_input, dim_input).inverse();
	}

	//


	long double prob_input = 0;

	//float prob_input = input_probability(input,Mean1,Sigma1);
	for (k = 0; k < dim_priors; k++) {
		 double prob_input_tmp = gausspdf(input, input_mean_matrix.col(k),
				Sigma_input.block(dim_input * k, 0, dim_input, dim_input));
		 double tmp_Pk = Priors(k) * prob_input_tmp;
		p(k) = tmp_Pk;
		prob_input = prob_input + tmp_Pk;

	}



	for (k = 0; k < dim_priors; k++) {
		 double h_k = p(k) / prob_input;
		h(k) = h_k;
	}

	for (k = 0; k < dim_input*dim_priors - dim_input; k = k + dim_input) {
		A_matrix.block(k, 0, dim_input, dim_input) = Sigma_output_input.block(k, 0, dim_input, dim_input) * Inverse_Sigma_input.block(k, 0, dim_input, dim_input);
	}

	for (k = 0; k < dim_priors; k++) {
		B_matrix.col(k) = out_mean_matrix.col(k) - A_matrix.block(dim_input * k, 0, dim_input, dim_input) * input_mean_matrix.col(k);
	}

	output.Zero(dim_input,1);

	for (k = 0; k < dim_priors; k++) {
		output = output + h(k) * (A_matrix.block(dim_input * k, 0, dim_input, dim_input) * input + B_matrix.col(k));

	}




//	long double output_array[dim_input];
	long double *output_array;
	output_array = (long double *)malloc(dim_input * 1 * sizeof(long double));

	for(i=0; i< dim_input;i++)
	{
		output_array[i] = output(i);
	}

	return output_array;
}
