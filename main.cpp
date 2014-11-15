/*
 * 09-11-2014
 * This is the fun
 */
#include"load_f_data.hpp"
#include </usr/include/eigen3/Eigen/Core>
#include <iostream>

using namespace Eigen;

int main()
{
	/*
	 * First initiate the class
	 */
	load_function_data load_obj;

	VectorXf Priors(6);
	Priors = load_obj.priors_tmp; /*!< an Eigen Vector value */

	MatrixXf Mean(6, 4);
	Mean = load_obj.mean_tmp;

	MatrixXf Sigma(24,4);
	Sigma = load_obj.sigma_tmp;

//	/*!< an Eigen Matrix value */

	std::cout << Sigma(0,0) << std::endl;

	return 0;
}


