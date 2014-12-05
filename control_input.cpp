/*
 * control_input.cpp
 *
 *  Created on: 04-Dec-2014
 *      Author: niladriisl
 */

#include </usr/include/eigen3/Eigen/Core>
#include <stdio.h>
#include <math.h>
#include <cmath>

using namespace Eigen;
using namespace std;

Eigen::VectorXf control_input(Eigen::VectorXf input, Eigen::VectorXf Grad_V,
		Eigen::VectorXf xi_star, Eigen::VectorXf f_estimate, float rho_0,
		float K) {
	int input_size = input.rows();
	Eigen::VectorXf control_input(input_size);
	float tmp_value1 = Grad_V.transpose() * f_estimate
			+ rho_0 * (1 - exp(-K * input.norm()));
	if (tmp_value1 <= 0 && input == xi_star) {
		control_input.Zero(input_size);
	}
	else if(input == xi_star)
	{
		control_input = -f_estimate;
	}
	else
	{
		control_input = -((tmp_value1)/(Grad_V.transpose()*Grad_V))*Grad_V;
	}
	return control_input;
}

