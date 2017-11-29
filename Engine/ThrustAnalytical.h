/**
*	@ingroup Engine
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	Base Thrust class is the superclass for all engine models. Using pointer to base
*	init and update function allows the user to extend the engine module with new
*	engine models.
*
*/
#include"BaseThrust.h"
#include"Constants.h"
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
	*/
	void initializeThrust(ThrustStruct & ThrustData,
						  AircraftStruct &AircraftData);

	/**
	*	@brief calculate thrust forces and moments
	*   @param FlightTime
	*	@param AtmoData	get current atmospheric data
	*	@param AeroData get mach number
	*	@param AirframeData	get current throttle stick position
	*	@return current thrust data is stored in ThrustStruct
	*/
	void calcThrust(Float64 FlightTime,					
					AtmosphereStruct & AtmoData,		
					AerodynamicStruct & AeroData,		
					AirframeStruct & AirframeData,		
					ThrustStruct & ThrustData);			

private:
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
	readInData *ReadInThrustData;		

};
#endif  THRUSTANALYTICAL_H
