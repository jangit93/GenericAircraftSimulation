/** @defgroup	Autopilot Autopilot
*	@author		Jan Olucak
*	@date		01.05.2018
*	@version	1.0
*
*	Autopilot class calls the desired type of controller.
*  @{
*/

#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include"MatFileReader.h"
#include"DataCloud.h"
#include"StateController.h"
#include"FindNeighbor.h"

class Autopilot
{
public: 
	/**
	* \brief constructor
	*/
	Autopilot();


	/**
	* \brief destructor
	*/
	~Autopilot();

	/**
	* \brief initialize autopilot
	*/
	void initAutopilot();

	/**
	* \brief calculate controlls
	* @param	FlightTime		flight time
	* @param	AirframeData	flight states
	* @param	AeroData		get angle of attack
	* @param	GuidanceData	control input
	* @param	ActuatorData	actuator angles
	* @param	IMUData			rotatory rates
	* @param	NavData			velocity
	*/
	void updateAutopilot(Float64 FlightTime, 
						AirframeStruct &AirframeData,
						AerodynamicStruct &AeroData,
						GuidanceStruct &GuidanceData,
						ActuatorStruct &ActuatorData, 
						IMUStruct &IMUData,
						NavigationStruct &NavData);

private:
	StateController *controller;

};
/**@}*/
#endif // !AUTOPILOT_H