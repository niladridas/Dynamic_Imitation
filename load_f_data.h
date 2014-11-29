/*
 * load_f_data.hpp
 *
 *  Created on: 11-Nov-2014
 *      Author: niladriisl
 */


#ifndef LOAD_F_DATA_H_
#define LOAD_F_DATA_H_

#include </usr/include/eigen3/Eigen/Core>

/*! A test class declaration */

class load_function_data
{

public:

  Eigen::VectorXf priors_tmp;/*!< an Eigen Vector value */
  Eigen::MatrixXf mean_tmp;/*!< an Eigen Matrix value */
  Eigen::MatrixXf sigma_tmp;/*!< an Eigen Matrix value */

public:

  load_function_data();  //! A constructor.
  /*!
  A more elaborate description of the constructor.
  */

  void read_priors(); //!< a member function.

  void read_means(); //!< a member function.

  void read_sigma(); //!< a member function.

  //! A destructor.
 /*!
 A more elaborate description of the destructor.
 */
  ~load_function_data();
};

#endif /* LOAD_F_DATA_HPP_ */
