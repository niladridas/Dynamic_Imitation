/*
 * control_input.h
 *
 *  Created on: 04-Dec-2014
 *      Author: niladriisl
 */

#ifndef CONTROL_INPUT_H_
#define CONTROL_INPUT_H_


#include </usr/include/eigen3/Eigen/Core>

using namespace Eigen;

Eigen::VectorXf control_input(Eigen::VectorXf input,Eigen::VectorXf Grad_V,Eigen::VectorXf xi_star, Eigen::VectorXf f_estimate,float rho_0, float K);

#endif /* CONTROL_INPUT_H_ */
