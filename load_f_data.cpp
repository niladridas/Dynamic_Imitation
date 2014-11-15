/*
 * load_f_data.cpp
 *
 *  Created on: 11-Nov-2014
 *      Author: niladriisl
 */
// A2DD.cpp

/// Brief description.
/** Detailed description. */

#include "load_f_data.hpp"
#include <fstream>
#include <iostream>
#include </usr/include/eigen3/Eigen/Core>

using namespace std;
using namespace Eigen;



  load_function_data::load_function_data():priors_tmp(Eigen::VectorXf()),mean_tmp(Eigen::MatrixXf()),sigma_tmp(Eigen::MatrixXf())
  {
	  read_priors();
	  read_means();
	  read_sigma();
  }



  void load_function_data::read_priors()
  {
/*
 * Read a file and save the variables in Priors
 */
	  ifstream file1;
	  file1.open( "/home/niladriisl/eclipse_workspace/Dynamic_Imitation/priors.txt");
	  priors_tmp.resize(6);
	  for(int i = 0; i < 6; i++)
	  {
	  file1 >> priors_tmp(i);
	  }
	  file1.close();
  }



  void load_function_data::read_means()
    {
  /*
   * Read a file and save the variables in means
   */
	  ifstream file2;
	  file2.open("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/mean.txt");
	  mean_tmp.resize(4,6);
	  for(int i = 0; i < 4; i++)
	  {
		  for(int j = 0; j < 6; j++)
		  	  {
			  file2 >> mean_tmp(i,j);
		  	  }
	  }
	  file2.close();
    }

  void load_function_data::read_sigma()
    {
  /*
   * Read a file and save the variables in sigma
   */
	ifstream file3;
	file3.open("/home/niladriisl/eclipse_workspace/Dynamic_Imitation/sigma.txt");
	sigma_tmp.resize(24,4);
	for (int i = 0; i < 24; i++)
			{
		for (int j = 0; j < 4; j++)
				{
			file3 >> sigma_tmp(i,j);
				}
			}
	file3.close();
    }

  load_function_data::~load_function_data(){}









