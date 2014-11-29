/*
 * gaussPdf.h
 *
 *  Created on: 29-Nov-2014
 *      Author: niladriisl
 */

#ifndef GAUSSPDF_H_
#define GAUSSPDF_H_

#include </usr/include/eigen3/Eigen/Core>

using namespace Eigen;

long double gausspdf(const VectorXf input, const VectorXf Mean,const MatrixXf Sigma); // input arguments are the query point, mean and the sigma

#endif /* GAUSSPDF_H_ */
