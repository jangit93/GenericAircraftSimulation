/**
*	@ingroup Aerodynamic
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	Base Aerodynamic class is the superclass for all aerodynamic models. Using pointer to base
*	init and update function allows the user to extend the aerodynamic module with new
*	models.
*
*/

#ifndef BASEAERODYNAMIC_H
#define BASEAERODYNAMIC_H

#include<math.h>
#include<iostream>
#include"DataCloud.h"
#include"IndependetDataTypes.h"
#include<Eigen/Dense>

class BaseAerodynamic {

public:
	/**
	*  @brief constructor
	*/
	BaseAerodynamic();

	/**
	*  @brief destructor
	*/
	~BaseAerodynamic();


	/**
	*  @brief The init function from the selected aerodynamic model is called by a pointer.
	*	@param	FlightTime			flighttime
	*	@param	AeroData			structure of aero data
	*	@param	AircraftData		structure of aircraft data
	*/
	virtual void initAerodynamic(Float64 &FlightTime,
								 AerodynamicStruct & AeroData,
								 AircraftStruct &AircraftData);


	/**
	*  @brief The update function from the selected aerodynamic model is called by a pointer.
	*	@param	FlightTime			Flight Time
	*	@param	AtmoData			structure of atmospheric data
	*	@param	AeroData			structure of aero data
	*	@param	AirframeData		structure of airframe data
	*	@param	ThrustData			structure of thrust data
	*/

	virtual void updateAerodynamic(Float64 &FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

	/**
	* \brief log aerodynamic data to text file
	*/
	virtual void LogAeroData();




};
#endif BASEAERODYNAMIC