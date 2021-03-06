/** @defgroup	Aerodynamic Aerodynamic
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Aerodynamic class is used to call the desired aerodynamic model. The engine model is selected from
*	General.dat input file.
*  @{
*/

#ifndef AERODYNAMIC_H
#define AERODYNAMIC_H

#include<math.h>
#include"DataCloud.h"
#include"readInData.h"
#include"IndependetDataTypes.h"
#include"BaseAerodynamic.h"
#include"DATCOMAerodynamic.h"


class Aerodynamics {

public:

	/**
	* \brief constructor
	*	@param	SimPref	 structure of model selctions
	*/
	Aerodynamics(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Aerodynamics();

	/**
	* \brief set pointer to desired class
	*	@param	type	Aerodynamic Model Selection
	*/
	void selectAerodynamicType(int type);

	/**
	* \brief initialize aerodynamic paramters
	*	@param	FlightTime		flighttime
	*	@param	AeroData		structure of aero data
	*	@param	AircraftData	structure of aircraft data
	*/
	void initAerodynamic(Float64 &FlightTime,
						 AerodynamicStruct &AeroData, 
						 AircraftStruct &AircraftData);

	/**
	* \brief calculate aero forces and moments
	*	@param	FlightTime			Flight Time
	*	@param	AtmoData			air density, speed of sound
	*	@param	AeroData			structure of aero data
	*	@param	AirframeData		structure of airframe data
	*	@param	ThrustData			structure of thrust data
	*	@param  ActuatorData		actuator angles
	*	@param	IMUData				rotational rates
	*	@param	NavData				Navigation data like velocity in NED system
	*/
	void updateAerodynamic(Float64 FlightTime,
							AtmosphereStruct &AtmoData,
							AerodynamicStruct &AeroData,
							AirframeStruct &AirframeData,
							ThrustStruct &ThrustData,
							ActuatorStruct &ActuatorData,
							IMUStruct &IMUData,
							NavigationStruct  &NavData);
	/**
	* \brief log aerodynamic data to text file
	*/
	void LogAeroData();

private:
	BaseAerodynamic * aerodynamic;
};
/**@}*/
#endif	AERODYNAMIC_H