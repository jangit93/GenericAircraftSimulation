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
	*  @brief The update function from the selected aerodynamic model is called by a pointer.
	*/
	void updateAerodynamic(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

	/**
	*  @brief The init function from the selected aerodynamic model is called by a pointer.
	*/
	void initAerodynamic(AerodynamicStruct & AeroData,
						 AircraftStruct &AircraftData);


	virtual void calcAerodynamic(Float64 FlightTime,
								AtmosphereStruct & AtmoData,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData);


	virtual void initializeAerodynamic(AerodynamicStruct & AeroData, 
									   AircraftStruct & AircraftData);

};
#endif BASEAERODYNAMIC