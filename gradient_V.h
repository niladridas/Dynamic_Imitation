/*
 * gradient_V.h
 *
 *  Created on: 04-Dec-2014
 *      Author: niladriisl
 */

#ifndef GRADIENT_V_H_
#define GRADIENT_V_H_

#include </usr/include/eigen3/Eigen/Core>

/*! A test class declaration */

class gradient_V {

public:

	Eigen::VectorXi lyapunovconfigdata;/*!<Lyapunov Function Configuration File*/
	// This file contains
	// 1. Number of input states 2. Number of asymmetric function
	Eigen::MatrixXf P_0_data;/*!< Symmetric Lyapunov component */
	Eigen::MatrixXf P_total_data;/*!< matrix containing all asymmetric components */
	Eigen::VectorXf Mu;

public:

	gradient_V(); //! A constructor.
	/*!
	 A more elaborate description of the constructor.
	 */
	void lyapunov_config();

	void P_0(); //!< a member function.

	void P_total(); //!< a member function.

	void Mu_read();

	Eigen::VectorXf calculate_gradient(const Eigen::VectorXf input,const Eigen::VectorXf xi_star); //!< a member function.


	//! A destructor.
	/*!
	 A more elaborate description of the destructor.
	 */
	~gradient_V();
};

#endif /* GRADIENT_V_H_ */
