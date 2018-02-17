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
#include"Autopilot.h"
#include"Guidance.h"
#include<iostream>

class Trajectory6Dof : public Trajectory3Dof
{
public:
	Trajectory6Dof();

	~Trajectory6Dof();


	virtual void initTrajectory(Float64 FlightTime, 
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,
								AircraftStruct &AircraftData,
								GuidanceStruct & GuidanceData,
								NavigationStruct &NavData,
								ActuatorStruct &ActuatorData,
								IMUStruct &IMUData);
	
	 void initTrajectory6Dof(Float64 FlightTime,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,
								AircraftStruct &AircraftData,
								GuidanceStruct & GuidanceData,
								NavigationStruct &NavData);
	
	virtual void updateTrajectory(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						GuidanceStruct & GuidanceData,
						NavigationStruct &NavData,
						ActuatorStruct &ActuatorData,
						IMUStruct &IMUData);

	void updateTrajectory6Dof(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							GuidanceStruct & GuidanceData,
							NavigationStruct &NavData);






private:
	Autopilot * autopilot;
	Guidance  *guidance;
	Airframe     *airframe;
	
};

#endif // TRAJECTORY3DOF_H