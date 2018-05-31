/**
*	@ingroup Guidance
*	@author Jan Olucak
*	@date 23.12.2017
*	@version 1.0
*
*	BaseGuidance is the superclass for all guidance models
*
*/

#ifndef BASEGUIDANCE_H
#define BASEGUIDANCE_H



#include<iostream>
#include"DataCloud.h"
#include"IndependetDataTypes.h"

class BaseGuidance 
{
public:
	/**
	* \brief constructor
	*/
	BaseGuidance();

	/**
	* \brief destructor
	*/
	~BaseGuidance();

	/**
	* \brief accTables are read in and stored in row vectors
	*	@param	FlightTime			flight time
	*	@param	GuidanceData		structure of Guidance data
	*	@param	AircraftData		specific airfraft data
	*/
	virtual void initGuidance(Float64 &FlightTime, GuidanceStruct &GuidanceData,AircraftStruct &AircraftData);

	/**
	* \brief calculate commands for flight path
	*	@param	FlightTime			flight time
	*	@param	AeroData			structure of aero data
	*	@param	ThrustData			structure of thrust data
	*	@param	AirframeData		structure of airframe data
	*	@param	GuidanceData		structure of guidance data
	*/
	virtual void updateGuidance(Float64 FlightTime,
						AerodynamicStruct &AeroData,
						ThrustStruct &ThrustData,
						AirframeStruct &AirframeData,
						GuidanceStruct &GuidanceData);

	/**
	* \brief define output for guidance data
	*	@param	FlightTime			flight time
	*	@param	GuidanceData		structure of guidance data
	*/
	virtual void initLogGuidance(Float64 FlightTime, 
								 GuidanceStruct &GuidanceData);

	/**
	* \brief log guidance data
	*/
	virtual void logGuidanceData();


private:

};
#endif BASEGUIDANCE_H