#ifndef LINEARINTERPOLATION_H
#define LINEARINTERPOLATION_H

#include <vector>
#include"../EIGENDIR/Eigen/Dense"
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
	LinearInterpolation();

	~LinearInterpolation();

	Float64 searchIndex(VectorXd Vector,
						Float64 Value);

	Float64 linearInterpolation2D(VectorXd Vector1,
								  VectorXd Vector2,
								  MatrixXd Table,
								  Float64 Value1,
								  Float64 Value2);

	Float64 linearInterpolation1D(VectorXd Vector1,
								VectorXd Table,
								Float64 Value);
private:
	Int32		index1;
	Int32		index2;
	Float64     dx;
	Float64		dy;
	Float64     dx_inv;
	Float64		dy_inv;
	Float64	    interpolationValue;

};
#endif LINEARINTERPOLATION_H