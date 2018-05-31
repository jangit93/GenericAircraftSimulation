/** @ingroup	Tools
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Transformation class provides transformation matrices for flightmechanical coordinate sytems
*  @{
*/

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H


#include<iostream>
#include<Eigen/dense>
#include"IndependetDataTypes.h"

class Transformation
{
public:
	/**
	* \brief constructor
	*/
	Transformation();

	/**
	* \brief destructor
	*/
	~Transformation();

	/**
	* \brief tranformation matrix from NED system to body fixed system
	* @param phi roll angle
	* @param theta pitch angle
	* @param psi heading angle
	*/
	Eigen::Matrix3d MatNedToBody(Float64 phi, Float64 theta, Float64 psi);

	/**
	* \brief tranformation matrix from Body system to NED system 
	* @param MatNedToBody invers matrix
	*/
	Eigen::Matrix3d MatBodyToNED(Eigen::Matrix3d MatNedToBody);

	/**
	* \brief tranformation matrix from NED system to trajectory system
	* @param Gamma  
	* @param chi azimuth
	*/
	Eigen::Matrix3d MatNEDToTrajectory(Float64 Gamma, Float64 chi);

	/**
	* \brief tranformation matrix from aerodynamic system to body fixed system
	* @param Alpha angle of attack
	* @param Beta angle of sideslip
	*/
	Eigen::Matrix3d MatAeroToBody(Float64 Alpha, Float64 Beta);

private:

	Eigen::Matrix3d matNEDtoBody;
	Eigen::Matrix3d matBodytoNED;
	Eigen::Matrix3d matNEDtoTrajectory;
	Eigen::Matrix3d matAerotoBody;


};
#endif TRANSFORMATION_H