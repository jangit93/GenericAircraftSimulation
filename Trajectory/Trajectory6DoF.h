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
#include"ODESolver.cpp"
#include<iostream>

class Trajectory6Dof : public Trajectory3Dof
{
public:
	/**
	*	@brief constructor
	*	@param	SimPref	mode selection for trajectory
	*/
	Trajectory6Dof(SimDPreference &SimPref);

	/**
	*	@brief destructor
	*/
	~Trajectory6Dof();

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
	* @brief initalize 6Dof trajectory
	* @param FlightTime flight time
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	* @param AircraftData	geometric data of aircraft
	* @param GuidanceData control variables
	* @param NavData aircraft position, velocity
	*/
	 void initTrajectory6Dof(Float64 &FlightTime,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData,
								AircraftStruct &AircraftData,
								GuidanceStruct & GuidanceData,
								NavigationStruct &NavData);
	
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
	* @brief calculate 6Dof trajectory
	* @param FlightTime flight time
	* @param AtmoData current atmospheric data
	* @param AeroData aerodynamic data
	* @param AirframeData flight states
	* @param ThrustData  thrust forces and moments
	* @param GuidanceData control variables
	* @param NavData aircraft position, velocity
	*/
	void updateTrajectory6Dof(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData,
							GuidanceStruct & GuidanceData,
							NavigationStruct &NavData, ActuatorStruct &ActuatorData);
	/**
	* @brief integrate accelerations and calculate new flight states
	* @param AirframeData flight statess
	*/
	void integrationTrajectory(AirframeStruct &AirframeData);

	/**
	* @brief log 6Dof Trajectory data 
	*/
	void log6DofData();



private:
	Float64 dt;
	Autopilot * autopilot;
	Guidance  *guidance;
	Airframe     *airframe;
	Transformation *Trafo;
	
};

#endif // TRAJECTORY3DOF_H