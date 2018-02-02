/** @defgroup	Airframe Airframe
*	@author		Jan Olucak
*	@date		27.11.2017
*	@version	1.0
*
*	Airframe class calculates body fixed acceleration
*  @{
*/
#ifndef AIRFRAME_H
#define AIRFRAME_H

#include<iostream>
#include"DataCloud.h"
#include"readInData.h"
#include"Constants.h"
#include<Eigen/Dense>


class Airframe
{
public:
	/**
	* \brief constructor
	*/
	Airframe();

	/**
	* \brief destructor
	*/
	~Airframe();

	/**
	* \brief Airframe initialization 
	* Airframe and Aircraft Data are initialized. Parameters from Aircraft.dat are read in and stored in their specific structure
	*/
	void initAirframe(AircraftStruct	&AircraftData,
					  AirframeStruct	&AirframeData);

	/**
	* \brief translational equations of motion
	* translational body accelerations are calculated
	* @param AeroData Aerodynamic forces,moments and angles
	* @param ThrustData Thrust forces and moments
	* @param AircraftData aircraft mass
	* @return Data stored in AirframeStruct
	*/
	void updateTranslational(AerodynamicStruct  &AeroData,
							 ThrustStruct		&ThrustData,
							AirframeStruct &AirframeData);

	/**
	* \brief rotational equations of motion
	* rotation body accelerations are calculated. Euler angle derivatives,too.
	* @param AeroData Aerodynamic moments and angles
	* @param ThrustData Thrust forces and moments
	* @param AircraftData aircraft mass
	* @return Data stored in AirframeStruct
	*/
	void updateRotational(AerodynamicStruct  &AeroData,
							ThrustStruct		&ThrustData,
							AirframeStruct &AirframeData);


private:
	Float64 mass;
	readInData *readIn;
	Eigen::Vector3d Vec_fg;
	Eigen::Vector3d Vec_rotTensor;
	Float64 theta;
	Float64 phi;
	Float64 p;
	Float64 q;
	Float64 r;
	Float64 AoA;
	Float64 AoS;
	Eigen::Vector3d TotalForce;
	Eigen::Vector3d TotalMoment;
	Eigen::Matrix3d Eulerdot;
	Eigen::Vector3d rotRates;

};
/**@}*/

#endif 
