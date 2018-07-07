/** @defgroup	Aircaft Aircraft
*	@author		Jan Olucak
*	@date		14.12.2017
*	@version	1.0
*
*	Aircraft class simulates the trajectory of the designed aircraft. 
*  @{
*/

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include"../DataCloud/DataCloud.h"
#include"MatFileReader.h"
#include"Trajectory.h"
#include"Atmosphere.h"
#include<omp.h>

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
	* \brief simulation of aircraft
	*/
	void simulateAircraft();


	

private:
	
	//objects of classes
	Trajectory		*trajectory;
	Atmopshere		*Atmo;
	AutopilotStruct *TrimPoints;

	//structures
	AirframeStruct		AirframeData;
	AtmosphereStruct	AtmoData;
	AerodynamicStruct	AeroData;
	ThrustStruct		ThrustData;
	AircraftStruct		AircraftData;
	GuidanceStruct		GuidanceData;
	NavigationStruct	NavData;
	ActuatorStruct		ActuatorData;
	IMUStruct			IMUData;

	//simulation data
	Float64		FlightTime;
	int			Fields;
	int			TotalSimTime;
	Float32		dt;
	int			start;
	int			stride;
	int			edge; 
	int			copy_field;
	Float64		time1;
	Float64		tstart;


};
/**@}*/
#endif AIRCRAFT_H