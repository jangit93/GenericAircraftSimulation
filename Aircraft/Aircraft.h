/** @defgroup	Aircaft Aircraft
*	@author		Jan Olucak
*	@date		14.12.2017
*	@version	1.0
*
*	Aircraft class simulates the actual trajectory of the designed aircraft. 
*  @{
*/

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include"../DataCloud/DataCloud.h"
#include"MatFileReader.h"
#include"Trajectory.h"
#include"Atmosphere.h"

class Aircraft
{
public:
	/**
	* \brief construtor
	* @param SimPref prefered models for aircraft
	*/
	Aircraft(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Aircraft();

	/**
	* \brief initalize aircraft with desired models and parameters
	*/
	void initAircraft();

	/**
	* \brief simulation of aircraft
	*/
	void simulateAircraft();


	

private:
	
	Trajectory * trajectory;
	Atmopshere *Atmo;
	AutopilotStruct * TrimPoints;
	Float64 FlightTime;
	AirframeStruct AirframeData;
	AtmosphereStruct	AtmoData;
	AerodynamicStruct	AeroData;
	ThrustStruct		ThrustData;
	AircraftStruct		AircraftData;
	GuidanceStruct		GuidanceData;
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;
	IMUStruct IMUData;
	int Fields;
	int TotalSimTime;
	Float32 dt;


};
/**@}*/
#endif AIRCRAFT_H