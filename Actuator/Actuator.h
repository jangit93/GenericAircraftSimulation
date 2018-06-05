/** @defgroup	Actuator Actuator
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Actuator module simulates the actuators of an aircraft. 
*  @{
*/

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include"DataCloud.h"
#include"BaseActuator.h"
#include"flawlessActuator.h"
#include<iostream>

class Actuator
{
public:
	/**
	* \brief constructor
	* @param SimPref	Selected Actuator model
	*/
	Actuator(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Actuator();


	/**
	* \brief initialize selected actuator model
	* @param FlightTime Flight time
	* @param AirframeData coammanded actuator angles from autopilot
	* @param ActuatorData real Actuator angles
	*/
	void initActuator(Float64 &FlightTime,
					  AirframeStruct & AirframeData, 
					  ActuatorStruct &ActuatorData);

	/**
	* \brief switch function to select desired model
	* @param type selected model (as integer value9
	*/
	void selectActuatorType(int type);

	/**
	* \brief update actuator model
	* @param FlightTime Flight time
	* @param AirframeData coammanded actuator angles from autopilot
	* @param ActuatorData real Actuator angles
	*/
	void updateActuator(Float64 FlightTime,
						AirframeStruct & AirframeData,
						ActuatorStruct &ActuatorData);

	/**
	* \brief data logger for actuator data
	*/
	void logActuator();

private:
	BaseActuator * actuator;
};

/**@}*/
#endif	ACTUATOR_H