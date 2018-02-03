/** @defgroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		28.11.2017
*	@version	1.0
*
*	BaseTrajectory is the superclass for all trajectory classes.
*  @{
*/

#ifndef TRAJECTORY6DOF_H
#define TRAJECTORY6DOF_H

#include"BaseTrajectory.h"
#include"Trajectory3DoF.h"
#include"Engine.h"
#include"Aerodynamic.h"
#include"Airframe.h"
#include<iostream>

class Trajectory6Dof : public Trajectory3Dof
{
public:
	Trajectory6Dof();

	~Trajectory6Dof();
	/*
	void initTrajectory(AerodynamicStruct & AeroData,
		AirframeStruct & AirframeData,
		ThrustStruct & ThrustData,
		AircraftStruct &AircraftData,
		AutopilotStruct & AutopilotData,
		GuidanceStruct & GuidanceData);

	void updateTrajectory(Float64 FlightTime,
		AtmosphereStruct & AtmoData,
		AerodynamicStruct & AeroData,
		AirframeStruct & AirframeData,
		ThrustStruct & ThrustData,
		AutopilotStruct & AutopilotData,
		GuidanceStruct & GuidanceData);
*/
private:
	//Engine * engine;
	//Aerodynamics *aerodynamics;
	//Airframe     *airframe;
	
};

#endif // TRAJECTORY3DOF_H