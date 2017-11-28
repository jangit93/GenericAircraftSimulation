/** @defgroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		28.11.2017
*	@version	1.0
*
*	BaseTrajectory is the superclass for all trajectory classes.
*  @{
*/

#ifndef TRAJECTORY3DOF_H
#define TRAJECTORY3DOF_H

#include"BaseTrajectory.h"
#include"Engine.h"
#include"Aerodynamic.h"
#include<iostream>

class Trajectory3Dof : public BaseTrajectory
{
public:
	Trajectory3Dof();

	~Trajectory3Dof();

	void initializeTrajectory();

	void calcTrajectorythis(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

private:
	Engine		 *engine;
	Aerodynamics *aerodynamics;
};

#endif // TRAJECTORY3DOF_H
