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
							AutopilotStruct &AutopilotData,
							GuidanceStruct &GuidanceData);

	virtual void initializeTrajectory(AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData,
										AircraftStruct &AircraftData, 
									 AutopilotStruct & AutopilotData,
									 GuidanceStruct & GuidanceData);

	virtual void calcTrajectory(Float64 FlightTime,
								AtmosphereStruct & AtmoData,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,
								AutopilotStruct & AutopilotData,
								GuidanceStruct & GuidanceData);


private:
	


};

#endif