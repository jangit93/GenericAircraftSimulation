/** @defgroup	Autopilot Autopilot
*	@author		Jan Olucak
*	@date		15.01.2018
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
	*/
	void updateAutopilot(Float64 FlightTime, 
						AirframeStruct &AirframeData,
						AerodynamicStruct &AeroData,
						GuidanceStruct &GuidanceData);

private:
	StateController *controller;

};
/**@}*/
#endif // !AUTOPILOT_H