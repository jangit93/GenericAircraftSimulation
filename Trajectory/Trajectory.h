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
	/**
	*	@brief constructor
	*	@param	SimPref	mode selection for trajectory
	*/
	Trajectory(SimDPreference &SimPref);

	/**
	*	@brief destructor
	*/
	~Trajectory();

	/**
	*	@brief switch function to select desired trajecotry model
	*	@param type trajectory model
	*	@param	SimPref	selection of module models
	*/
	void selectTrajectory(int type,
						  SimDPreference &SimPref);

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
	*	@brief log trajectory data
	*/
	void logTraj();
private:
	BaseTrajectory *traj;
	
};
/**@}*/
#endif