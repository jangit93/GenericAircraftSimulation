/** @defgroup	Guidance Guidance
*	@author		Jan Olucak
*	@date		01.04.2018
*	@version	1.0
*
*	Guidance class is used to call the desired Guidance model.
*  @{
*/

#ifndef GUIDANCE_H
#define GUIDANCE_H

#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseGuidance.h"
#include"accTable.h"
#include"../Tools/DataLogger.h"

class Guidance
{
public:
	/**
	* \brief constructor
	* @param SimPref	Structure with model selection
	*/
	Guidance(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Guidance();

	/**
	* \brief set pointer to desired class
	*	@param	Type			Aerodynamic Model Selection
	*/
	void selectGuidance(int Type);

	/**
	* \brief initialize desired Guidance Model
	*	@param	FlightTime			flight time
	*	@param	GuidanceData		structure of Guidance data
	*	@param	AircraftData		specific airfraft data
	*/
	void initGuidance(Float64 &FlightTime,
					  GuidanceStruct &GuidanceData, 
					  AircraftStruct &AircraftData);

	/**
	* \brief calculate commands for flight path
	*	@param	FlightTime			flight time
	*	@param	AeroData			structure of aero data
	*	@param	ThrustData			structure of thrust data
	*	@param	AirframeData		structure of airframe data
	*	@param	GuidanceData		structure of guidance data
	*/
	void updateGuidance(Float64 FlightTime, 
						AerodynamicStruct & AeroData, 
						ThrustStruct & ThrustData,
						AirframeStruct & AirframeData, 
						GuidanceStruct & GuidanceData);
	/**
	* \brief log guidance data
	*/
	void logGuidanceData();


private:
	BaseGuidance * guidance;
};
/**@}*/
#endif	GUIDANCE_H