/**
*	@defgroup Engine Engine
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	Engine class is used to call the desired engine model. The engine model is selected from 
*	General.dat input file. 
*  @{
*/

#include"BaseThrust.h"
#include"ThrustAnalytical.h"

#ifndef ENGINE_H
#define ENGINE_H


class Engine
{
public:
	/**
	*	@brief constructor
	*	@param	SimPref	mode selection for engine
	*/
	Engine(SimDPreference &SimPref);

	/**
	*  @brief destructor
	*/
	~Engine();

	/**
	*  @brief select Engine Type depending on input file
	*  @param type	specific integer to select desired engine
	*/
	void selectEngineType(int type);

	/**
	*	@brief initilization of engine specific data
	*   @param FlightTime flight time
	*	@param	ThrustData		structure of engine data
	*	@param	AircraftData	structure of aircraft data
	*/
	void initEngine(Float64 &FlightTime, 
					ThrustStruct & ThrustData,
					AircraftStruct &AircraftData);

	/**
	*  The update function from the selected engine is called by a pointer.
	*   @param FlightTime flight time
	*	@param AtmoData	get current atmospheric data
	*	@param AeroData get mach number
	*	@param AirframeData	get current throttle stick position
	*	@param ThrustData store thrust data
	*/
	void updateEngine(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

	/**
	*  @brief log engine data
	*/
	void logEngineData();

private:
	BaseThrust * Thrust;


};

#endif // !ENGINE_H