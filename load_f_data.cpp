/*
 * load_f_data.cpp
 *
 *  Created on: 11-Nov-2014
 *      Author: niladriisl
 */
// A2DD.cpp
/// Brief description.
/** Detailed description. */

#include "load_f_data.h"
#include <fstream>
#include <iostream>
#include </usr/include/eigen3/Eigen/Core>

using namespace std;
using namespace Eigen;

load_function_data::load_function_data() :
		priors_tmp(Eigen::VectorXf()), mean_tmp(Eigen::MatrixXf()), sigma_tmp(
				Eigen::MatrixXf()), xistar_tmp(Eigen::VectorXf()), sys_config(
				Eigen::VectorXi()) {
	read_sysconfig();
	read_priors();
	read_means();
	read_sigma();
	read_xistar();
}

void load_function_data::read_sysconfig()
{

	/*
	 * Read a file and save the variables in Priors
	 */
	ifstream file0;
	file0.open( "/home/niladriisl/eclipse_workspace/Dynamic_Imitation/sysconfig.txt");
	sys_config.resize(2);
	for(int i = 0; i < 2; i++)
	{
		file0 >> sys_config(i);
	}
	file0.close();
}


void load_function_data::read_priors() {
	/*
	 * Read a file and save the variables in Priors
	 */
	ifstream file1;
	file1.open(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/priors.txt");
	int tmp_tmp_prior_size = sys_config(1);

	priors_tmp.resize(tmp_tmp_prior_size);
	for (int i = 0; i < tmp_tmp_prior_size; i++) {
		file1 >> priors_tmp(i);
	}
	file1.close();
}

void load_function_data::read_means() {
	/*
	 * Read a file and save the variables in means
	 */
	ifstream file2;
	file2.open("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/mean.txt");
	int tmp_tmp_mean_row = sys_config(0); // number of input+output variables
	int tmp_tmp_mean_col = sys_config(1); // Number of gaussian components



	mean_tmp.resize(tmp_tmp_mean_row, tmp_tmp_mean_col);


	for (int i = 0; i < tmp_tmp_mean_row; i++) {
		for (int j = 0; j < tmp_tmp_mean_col; j++) {
			file2 >> mean_tmp(i, j);
		}
	}
	file2.close();
}

void load_function_data::read_sigma() {
	/*
	 * Read a file and save the variables in sigma
	 */
	ifstream file3;
	file3.open(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/sigma.txt");
	int tmp_tmp_sigma_row = sys_config(0)*sys_config(1);
		int tmp_tmp_sigma_col = sys_config(0);


	sigma_tmp.resize(tmp_tmp_sigma_row, tmp_tmp_sigma_col);

	for (int i = 0; i < tmp_tmp_sigma_row; i++) {
		for (int j = 0; j < tmp_tmp_sigma_col; j++) {
			file3 >> sigma_tmp(i, j);
		}
	}
	file3.close();
}

void load_function_data::read_xistar() {
	/*
	 * Read a file and save the variables in xi_star
	 */
	ifstream file4;
	file4.open(
			"/home/niladriisl/eclipse_workspace/Dynamic_Imitation/xi_star.txt");
	int tmp_tmp_mean_row = sys_config(0); // number of input+output variables
	xistar_tmp.resize(tmp_tmp_mean_row/2);
//	cout << "hi haha from inside  " << tmp_tmp_mean_row/2 << endl;

	for (int i = 0; i < tmp_tmp_mean_row/2; i++) {
			file4 >> xistar_tmp(i);
	}
	file4.close();
}

load_function_data::~load_function_data() {
}

