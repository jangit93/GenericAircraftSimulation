/** @ingroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		01.05.2018
*	@version	1.0
*
*	RealSystemTrajectory is a child of Basetrajectory. A trajectory is calulated with  possible systems faults.
*  @{
*/

#ifndef REALSYSTEMTRAJECTORY_H
#define REALSYSTEMTRAJECTORY_H

#include"DataCloud.h"
#include"Trajectory6DoF.h"
#include"Autopilot.h"
#include"Guidance.h"
#include"Airframe.h"
#include"Navigation.h"
#include"IMU.h"
#include"Actuator.h"
#include"GPS.h"

class RealSystemTrajectory : public Trajectory3Dof
{
public:
	/**
	*	@brief constructor
	*/
	RealSystemTrajectory(SimDPreference &SimPref);


	/**
	*	@brief destructor
	*/
	~RealSystemTrajectory();

	/**
	* @brief initalize trajectory
	* @param FlightTime flight time
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	* @param AircraftData	geometric data of aircraft
	* @param GuidanceData control variables
	* @param NavData aircraft position, velocity
	* @param ActuatorData real actuator angles
	* @param IMUData measured acceleration
	*/
	void initTrajectory(Float64 &FlightTime,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData,
						GuidanceStruct &GuidanceData,
						NavigationStruct &NavData,
						ActuatorStruct &ActuatorData,
						IMUStruct &IMUData);

	/**
	* @brief calculate trajectory
	* @param FlightTime flight time
	* @param AtmoData current atmospheric data
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	* @param GuidanceData control variables
	* @param NavData aircraft position, velocity
	* @param ActuatorData real actuator angles
	* @param IMUData measured acceleration
	*/
	void updateTrajectory(Float64 FlightTime,
						  AtmosphereStruct & AtmoData,
						  AerodynamicStruct & AeroData,
						  AirframeStruct & AirframeData,
						  ThrustStruct & ThrustData,
						  GuidanceStruct & GuidanceData,
						  NavigationStruct &NavData,
						  ActuatorStruct &ActuatorData,
						  IMUStruct &IMUData);

	/**
	*	@brief log trajectory data
	*/
	void logRealsystemTrajectory();

private:
	Autopilot * autopilot;
	Guidance  *guidance;
	Airframe     *airframe;
	GPS *gps;

	IMU *imu;
	Navigation *navigation;
	Actuator *actuator;
};

#endif // !REALSYSTEMTRAJECTORY_H