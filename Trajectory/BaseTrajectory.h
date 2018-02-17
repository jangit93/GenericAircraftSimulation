/** @ingroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		28.11.2017
*	@version	1.0
*
*	BaseTrajectory is the superclass for all trajectory classes.
*  @{
*/

#ifndef BASETRAJECTORY_H
#define BASETRAJECTORY_H
#include"DataCloud.h"

class BaseTrajectory {
public:

	BaseTrajectory();

	~BaseTrajectory();

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
							GuidanceStruct &GuidanceData,
		NavigationStruct &NavData,
		ActuatorStruct &ActuatorData,
		IMUStruct &IMUData);


private:
	


};

#endif