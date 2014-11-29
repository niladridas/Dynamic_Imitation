/*
 * f_estimate.h
 *
 *  Created on: 29-Nov-2014
 *      Author: niladriisl
 */

#ifndef F_ESTIMATE_H_
#define F_ESTIMATE_H_

#include </usr/include/eigen3/Eigen/Core>

using namespace Eigen;

long double* f_estimate(const VectorXf input, const MatrixXf Mean,const MatrixXf Sigma, const VectorXf Priors);


#endif /* F_ESTIMATE_H_ */
