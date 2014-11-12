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
#include <Eigen/Core>
#include <stdlib.h>     /* div, div_t */

using namespace std;
using namespace Eigen;


MatrixXf** initialize_3dMatrix(MatrixXf** matrix, int sizes[], float value = 0.0)
{
	matrix = new MatrixXf*[sizes[0]];
	for (int d1 = 0; d1 < sizes[0]; d1++)
	{
			matrix[d1] = new (MatrixXf)(MatrixXf::Ones(sizes[2], sizes[3]).array() * value);
	}
	return (matrix);
}




  load_function_data::load_function_data()
  {
	  void read_priors();
	  void read_means();
	  void read_sigma();
  }

  load_function_data::~load_function_data(){}

  void load_function_data::read_priors()
  {
/*
 * Read a file and save the variables in Priors
 */
	  ifstream file1;
	  file1.open( "prior.txt");
	  VectorXf priors(6);
	  priors << 0, 0, 0, 0, 0, 0;
	  for(int i = 0; i < 6; i++) // 3-d points
	  {
	  file1 >> priors(i);
	  }
	  file1.close();
  }

  void load_function_data::read_means()
    {
  /*
   * Read a file and save the variables in means
   */
	  ifstream file2;
	  file2.open( "mean.txt");
	  MatrixXf mean(4,6);
	  mean << 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0;
	  for(int i = 0; i < 4; i++) // 3-d points
	  {
		  for(int j = 0; j < 6; j++) // 3-d points
		  	  {
			  file2 >> mean(i,j);
		  	  }
	  }
	  file2.close();
    }

  void load_function_data::read_sigma()
    {
  /*
   * Read a file and save the variables in sigma
   */

	int sizes[4] = { 1, 2, 3, 4 };
	MatrixXf ***sigma = initialize_4dMatrix(sigma, { 6, 4, 4 }, 0.0);
	ifstream file3;

	div_t divresult;

	for (int i = 0; i < 24; i++) // 3-d points
	{
		divresult = div(i, 4);
		for (int j = 0; j < 4; j++) // 3-d points
		{
			 (*sigma[divresult.quot])(divresult.rem,j);
		}
	}
	file3.close();




    }











