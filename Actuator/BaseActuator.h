/**
*	@ingroup Actuator
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	BaseActuator class is the superclass for all actuator models. Using pointer to base
*	init and update function allows the user to extend the actuators module with new
*	models.
*
*/
#ifndef BASEACTUATOR_H
#define BASEACTUATOR_H 



#include"../DataCloud/DataCloud.h"

class BaseActuator
{
public:	
	/**
	* \brief construtor
	*/
	BaseActuator();

	/**
	* \brief construtor
	*/
	~BaseActuator();

	/**
	* \brief initialize selected actuator model
	* @param FlightTime Flight time
	* @param AirframeData coammanded actuator angles from autopilot
	* @param ActuatorData real Actuator angles
	*/
	virtual void initActuator(Float64 & FlightTime,
							  AirframeStruct & AirframeData,
							  ActuatorStruct & ActuatorData);

	/**
	* \brief update actuator model
	* @param FlightTime Flight time
	* @param AirframeData coammanded actuator angles from autopilot
	* @param ActuatorData real Actuator angles
	*/
	virtual void updateActuator(Float64 & FlightTime,
								AirframeStruct & AirframeData,
								ActuatorStruct & ActuatorData);

	/**
	* \brief log Actuator data
	*/
	virtual void LogActuatorData();

private:

	

};
#endif BASEACTUATOR_H