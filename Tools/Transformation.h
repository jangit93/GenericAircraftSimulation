#pragma once

#include<iostream>
#include<Eigen/dense>
#include"IndependetDataTypes.h"

class Transformation
{
public:
	Transformation();

	~Transformation();

	Eigen::Matrix3d MatNedToBody(Float64 phi, Float64 theta, Float64 psi);

	Eigen::Matrix3d MatBodyToNED(Eigen::Matrix3d MatNedToBody);

	Eigen::Matrix3d MatNEDToTrajectory(Float64 Gamma, Float64 chi);

	Eigen::Matrix3d MatAeroToBody(Float64 Alpha, Float64 Beta);

private:

	Eigen::Matrix3d matNEDtoBody;
	Eigen::Matrix3d matBodytoNED;
	Eigen::Matrix3d matNEDtoTrajectory;
	Eigen::Matrix3d matAerotoBody;


};