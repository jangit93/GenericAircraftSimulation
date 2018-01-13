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
#ifndef BaseThrust_H
#define BaseThrust_H

#include<math.h>
#include"DataCloud.h"
#include"readInData.h"
#include"IndependetDataTypes.h"
#include<Eigen/Dense>


class BaseThrust {

public:
	/**
	*  @brief constructor
	*/
	BaseThrust();

	/**
	*  @brief destructor
	*/
	~BaseThrust();

	/**
	*  The update function from the selected engine is called by a pointer.
	*/
	void updateThrust(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);
	/**
	*  The init function from the selected engine is called by a pointer.
	*/
	void initThrust(ThrustStruct & ThrustData,
					AircraftStruct &AircraftData);

	/**
	*	@brief calculate thrust forces and moments
	*   @param FlightTime
	*	@param AtmoData	get current atmospheric data
	*	@param AeroData get mach number
	*	@param AirframeData	get current throttle stick position
	*	@return current thrust data is stored in ThrustStruct
	*/
	virtual void calcThrust(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);


	virtual void initializeThrust(ThrustStruct & ThrustData,
								  AircraftStruct &AircraftData);

};

#endif	BaseThrust_H