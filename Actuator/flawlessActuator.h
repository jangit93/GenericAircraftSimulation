/**
*	@ingroup Actuator
*	@author Jan Olucak
*	@date 01.05.2018
*	@version 1.0
*
*	flawlessActuator class is inherited from BaseActuator. 
*   It is the simplest model for an actuator
*
*/

#ifndef FLAWLESSACTUATOR_H
#define FLAWLESSACTUATOR_H

#include"BaseActuator.h"
#include"../Tools/DataLogger.h"

class flawlessActuator : public BaseActuator
{
public:
	/**
	* \brief construtor
	*/
	flawlessActuator();

	/**
	* \brief destructor
	*/
	~flawlessActuator();


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
	* \brief initialize selected actuator model
	* @param FlightTime Flight time
	* @param AirframeData coammanded actuator angles from autopilot
	* @param ActuatorData real Actuator angles
	*/
	virtual void updateActuator(Float64 FlightTime,
							    AirframeStruct & AirframeData,
								ActuatorStruct & ActuatorData);

	/**
	* \brief define parameters for logging
	* @param FlightTime Flight time
	* @param ActuatorData real Actuator angles
	*/
	void initLogActuatorData(Float64 & FlightTime,
							 ActuatorStruct & ActuatorData);


	/**
	* \brief log actuator data
	*/
	void LogActuatorData();

private:
	DataLogger * logActuatorData;



};
#endif FLAWLESSACTUATOR_HH