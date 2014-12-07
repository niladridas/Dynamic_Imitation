/*
 * gradient_V.cpp
 *
 *  Created on: 04-Dec-2014
 *      Author: niladriisl
 */

#include "gradient_V.h"
#include <fstream>
#include <iostream>
#include </usr/include/eigen3/Eigen/Core>

using namespace std;
using namespace Eigen;

gradient_V::gradient_V() :
		lyapunovconfigdata(Eigen::VectorXi()), P_0_data(Eigen::MatrixXf()), P_total_data(
				Eigen::MatrixXf()), Mu(Eigen::VectorXf()) {

	lyapunov_config();
//	cout << "hi haha " <<endl;


	P_0(); //!< a member function.



	P_total(); //!< a member function.

	Mu_read();



//	Eigen::VectorXf calculate_gradient(const Eigen::VectorXf input,
//			const Eigen::VectorXf xi_star);

//	calculate_gradient(xi_star); //!< a member function.

}

void gradient_V::lyapunov_config() {
	/*
	 * Read a file and save the variables in Priors
	 */

	ifstream file01;
	file01.open(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/lyapunov_config.txt");

	lyapunovconfigdata.resize(2);
	for (int i = 0; i < 2; i++) {
		file01 >> lyapunovconfigdata(i);
	}
	file01.close();
}

void gradient_V::P_0() {

	/*
	 * Read a file and save the variables in Priors
	 */
	ifstream file02;
	file02.open("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/P0.txt");
	int tmp_no_input_states = lyapunovconfigdata(0);


	P_0_data.resize(tmp_no_input_states, tmp_no_input_states);
	for (int i = 0; i < tmp_no_input_states; i++) {
		for (int j = 0; j < tmp_no_input_states; j++) {
			file02 >> P_0_data(i, j);
		}
	}
	file02.close();
}

void gradient_V::P_total() {

	/*
	 * Read a file and save the variables in Priors
	 */

	int tmp_no_input_states = lyapunovconfigdata(0);
	int tmp_no_asymmetric = lyapunovconfigdata(1);

	if (tmp_no_asymmetric != 0) {
		ifstream file03;
		file03.open(
				"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/P_total.txt");
		P_total_data.resize(tmp_no_input_states * tmp_no_asymmetric,
				tmp_no_input_states);
		for (int i = 0; i < tmp_no_input_states * tmp_no_asymmetric; i++) {
			for (int j = 0; j < tmp_no_input_states; j++) {
				file03 >> P_total_data(i, j);
			}
		}
		file03.close();
	}

}

void gradient_V::Mu_read() {

	/*
	 * Read a file and save the variables in Priors
	 */
	int tmp_no_asymmetric = lyapunovconfigdata(1);

	if (tmp_no_asymmetric != 0) {
		ifstream file04;
		file04.open(
				"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/Mu_total.txt");
		int tmp_no_input_states = lyapunovconfigdata(0);

		Mu.resize(tmp_no_input_states * tmp_no_asymmetric, 1);
		for (int i = 0; i < tmp_no_input_states * tmp_no_asymmetric; i++) {
			file04 >> Mu(i);
		}
		file04.close();
	}

}

Eigen::VectorXf gradient_V::calculate_gradient(const Eigen::VectorXf input,
		const Eigen::VectorXf xi_star) {



	int input_size = input.rows();



	Eigen::VectorXf gradient_value(input_size);
	Eigen::VectorXf grad_part_2(input_size);

//	cout << "hi haha " <<endl;
//	cout << "hi haha " << lyapunovconfigdata(1)  << endl;


	grad_part_2 = VectorXf::Zero(input_size);



	if (lyapunovconfigdata(1) == 0) {

		gradient_value = (gradient_V().P_0_data + gradient_V().P_0_data.transpose()) * (xi_star - input);

	}



	else {

//		Eigen::VectorXi beta(lyapunovconfigdata(0));

		for (int i = 0; i < lyapunovconfigdata(1); i++) {
			float tmp_argument = (xi_star.transpose() - input.transpose())
					* P_total_data.block(i * input_size, 0, input_size,
							input_size)
					* (xi_star - input
							- Mu.block(i * input_size, 0, input_size, 0));
			if (tmp_argument >= 0) {
				grad_part_2 =
						grad_part_2
								+ 2 * tmp_argument
										* ((P_total_data.block(i * input_size,
												0, input_size, input_size)
												+ P_total_data.block(
														i * input_size, 0,
														input_size, input_size).transpose())
												* (xi_star - input)
												- P_total_data.block(
														i * input_size, 0,
														input_size, input_size)
														* Mu.block(
																i * input_size,
																0, input_size,
																0));
			}

		}

		gradient_value = (P_0_data + P_0_data.transpose()) * (xi_star - input)
				+ grad_part_2;
	}

	return gradient_value;
}

gradient_V::~gradient_V() {
}

