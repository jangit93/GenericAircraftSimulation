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
#include"Airframe.h"
#include<iostream>

class Trajectory3Dof : public BaseTrajectory
{
public:
	Trajectory3Dof();

	~Trajectory3Dof();

	virtual void initTrajectory(Float64 FlightTime, 
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,
								AircraftStruct &AircraftData,
								GuidanceStruct & GuidanceData,
								NavigationStruct &NavData,
								ActuatorStruct &ActuatorData,
								IMUStruct &IMUData);

	virtual void updateTrajectory(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							GuidanceStruct & GuidanceData,
							NavigationStruct &NavData,
							ActuatorStruct &ActuatorData,
							IMUStruct &IMUData);

	void initTrajectory3DoF(Float64 FlightTime, 
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							AircraftStruct &AircraftData);

	void updateTrajectory3DoF(Float64 FlightTime,
								AtmosphereStruct & AtmoData,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData);

	void logData(Float64 FlightTime,
		AtmosphereStruct & AtmoData,
		AerodynamicStruct & AeroData,
		AirframeStruct & AirframeData,
		ThrustStruct & ThrustData);
protected:
	Airframe * airframe;
private:
	Engine		 *engine;
	Aerodynamics *aerodynamics;
	
};

#endif // TRAJECTORY3DOF_H
