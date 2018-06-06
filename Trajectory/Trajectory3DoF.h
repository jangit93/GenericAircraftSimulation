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
#include"Aerodynamic.h"
#include"Airframe.h"
#include<iostream>
#include"Engine.h"

class Trajectory3Dof : public BaseTrajectory
{
public:

	/**
	*	@brief constructor
	*	@param	SimPref	mode selection for trajectory
	*/
	Trajectory3Dof(SimDPreference &SimPref);

	/**
	*	@brief destructor
	*/
	~Trajectory3Dof();

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
							GuidanceStruct & GuidanceData,
							NavigationStruct &NavData,
							ActuatorStruct &ActuatorData,
							IMUStruct &IMUData);

	/**
	* @brief initalize 3 Dof trajectory 
	* @param FlightTime flight time
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	* @param AircraftData	geometric data of aircraft
	*/
	void initTrajectory3DoF(Float64 &FlightTime, 
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							AircraftStruct &AircraftData);

	/**
	* @brief calculate 3 Dof trajectory
	* @param FlightTime flight time
	* @param AtmoData current atmospheric data
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	*/
	void updateTrajectory3DoF(Float64 FlightTime,
								AtmosphereStruct & AtmoData,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,ActuatorStruct &ActuatorData);

	/**
	* @brief log 3Dof Data (Aerodynamic Data, Thrust Data and translational acclerations)
	*/
	void log3DofData();

private:
	Engine		 *engine;
	Aerodynamics *aerodynamics;
	Airframe * airframe;
	
};

#endif // TRAJECTORY3DOF_H
