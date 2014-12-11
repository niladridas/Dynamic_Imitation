/*
 * gaussPdf.cpp
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

const double pi = boost::math::constants::pi<double>();

 double gausspdf(const VectorXf input, const VectorXf Mean,
		const MatrixXf Sigma) // input arguments are the query point, mean and the sigma
		{
	int input_size = input.rows(); // finding the input size
	double det_tmp = Sigma.determinant();
	double pow_tmp = fabs(det_tmp);
	double det_pow = 0.5;
	double det_tmp_tmp = pow(pow_tmp, det_pow);
	double coeff = pow((2 * pi), input_size / 2)
			* det_tmp_tmp;

//	long double


	 double exponential_part = -0.5
			* ((input - Mean).transpose() * Sigma.inverse()) * (input - Mean);

	double result = (1 / coeff) * exp(exponential_part);

//    std::cout << result << std::endl;

	return result;

}

