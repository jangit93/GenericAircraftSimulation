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
	/**
	*	@brief constructor
	*/
	BaseTrajectory();

	/**
	*	@brief destructor
	*/
	~BaseTrajectory();

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
	virtual void initTrajectory(Float64 &FlightTime, 
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData, 
						GuidanceStruct & GuidanceData,
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
	virtual void updateTrajectory(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							GuidanceStruct &GuidanceData,
							NavigationStruct &NavData,
							ActuatorStruct &ActuatorData,
							IMUStruct &IMUData);
	/**
	*	@brief log trajectory data
	*/
	virtual void logTraj();


private:
	


};

#endif