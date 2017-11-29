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

class Trajectory {

public:

	Trajectory();

	~Trajectory();

	void selectTrajectory(int type);

	void updateTrajectory(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AutopilotStruct & AutopilotData,
						GuidanceStruct & GuidanceData);

	void initTrajectory(AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData,
						AutopilotStruct &AutopilotData,
						GuidanceStruct &GuidanceData);

private:
	BaseTrajectory *traj;

};

#endif