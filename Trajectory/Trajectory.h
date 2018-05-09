/** @defgroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		28.11.2017
*	@version	1.0
*
*	BaseTrajectory is the superclass for all trajectory classes.
*  @{
*/

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include"BaseTrajectory.h"
#include"Trajectory3DoF.h"
#include"Trajectory6DoF.h"
#include"RealSystemTrajectory.h"

class Trajectory {

public:

	Trajectory(SimDPreference &SimPref);

	~Trajectory();

	void selectTrajectory(int type,SimDPreference &SimPref);

	void updateTrajectory(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						GuidanceStruct & GuidanceData, 
						NavigationStruct &NavData, 
						ActuatorStruct &ActuatorData, 
						IMUStruct &IMUData);

	void initTrajectory(Float64 FlightTime, 
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData,
						GuidanceStruct &GuidanceData,
						NavigationStruct &NavData,
						ActuatorStruct &ActuatorData,
						IMUStruct &IMUData);

	void logTraj();
private:
	BaseTrajectory *traj;
	
};

#endif