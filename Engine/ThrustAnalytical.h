/**
*	@ingroup Engine
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	ThrustAnalytical class is a child class of BaseThrust class.
*	Thrust forces and moments are calculated with an analytical model.
*
*/
#include"BaseThrust.h"
#include"Constants.h"
#include"DataLogger.h"
#include<math.h>

#ifndef THRUSTANALYTICAL_H
#define THRUSTANALYTICAL_H


class ThrustAnalytical : public BaseThrust {
public:

	/**
	*  @brief constructor
	*/
	ThrustAnalytical();

	/**
	*  @brief destructor
	*/
	~ThrustAnalytical();

	/**
	*  @brief read in Data from Engine.dat
	*   @param FlightTime flight time
	*	@param	ThrustData		structure of engine data
	*	@param	AircraftData	structure of aircraft data
	*/
	void initThrust(Float64 &FlightTime, 
					ThrustStruct & ThrustData,
					AircraftStruct &AircraftData);

	/**
	*  The update function from the selected engine is called by a pointer.
	*   @param FlightTime flight time
	*	@param AtmoData	get current atmospheric data
	*	@param AeroData get mach number
	*	@param AirframeData	get current throttle stick position
	*	@param ThrustData store thrust data
	*	@param ActuatorData get thrust stick positions
	*/
	void updateThrust(Float64 FlightTime,					
					  AtmosphereStruct & AtmoData,		
					  AerodynamicStruct & AeroData,		
					  AirframeStruct & AirframeData,		
					  ThrustStruct & ThrustData, 
					  ActuatorStruct& ActuatorData);

	/**
	*  @brief define output of thrust data
	*/
	void initLogEngineData(Float64 &FlightTime,
							ThrustStruct &ThrustData);

	/**
	*  @brief log engine data
	*/
	virtual void logEngineData();

private:
	//objects
	DataLogger * LogEngineData;
	readInData ReadInThrustData;

	//variables
	Eigen::Vector3d ThrustForce;		
	Eigen::Vector3d ThrustMoment;		
	Float64 rho;						
	Float64 Mach;						
	Float64 ThrottlePosition;			
	Float64 absThrust;					
	int maxThrust;						
	Float64 Kt;							
	Float64 incidenceAngle;				
	Eigen::Vector3d EnginePos;		
	Float64 thrust;

};
#endif  THRUSTANALYTICAL_H
