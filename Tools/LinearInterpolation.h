/** @ingroup	Tools 
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Data Logger is a class to write simulation data to an outputfile.
*  @{
*/

#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

#include <vector>
#include<Eigen/Dense>
#include<math.h>
#include<algorithm>


using Eigen::MatrixXd;
using Eigen::Vector3f;
using Eigen::MatrixX2f;
using Eigen::VectorXd;
using Eigen::Map;

typedef double Float64;
typedef int    Int32;

class LinearInterpolation{
public:
	/**
	* \brief constructor
	*/
	LinearInterpolation();

	/**
	* \brief destructor
	*/
	~LinearInterpolation();

	/**
	* \brief searches index of of a specific value in a vector/matrix
	*  @param Vector specific vector to search for index
	*  @param Value  wanted value
	*/
	Float64 searchIndex(VectorXd Vector,
						Float64 Value,
						Int32 aIndex);

	/**
	* \brief 2D linear interpolation
	*  @param Vector1 vector that defines lines of a table
	*  @param Vector2 vector that defines columns of a table
	*  @param Table   specific table
	*  @param Value1  wanted value of line vector
	*  @param Value2  wanted value of column vector
	*/
	Float64 linearInterpolation2D(VectorXd Vector1,
								  VectorXd Vector2,
								  MatrixXd Table,
								  Float64 Value1,
								  Float64 Value2);

	/**
	* \brief 1D linear interpolation
	*  @param vector that defines lines of a vector
	*  @param Table  specific data vector
	*  @param Value  wanted value
	*/
	Float64 linearInterpolation1D(VectorXd Vector1,
								VectorXd Table,
								Float64 Value);
private:
	Int32		index1;
	Int32		index2;
	Int32       Index;
	Int32		index;
	Float64     dx;
	Float64		dy;
	Float64     dx_inv;
	Float64		dy_inv;
	Float64	    interpolationValue;

};
#endif LINEARINTERPOLATION_H