/**
*	@ingroup Aerodynamic
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	DATCOm aerodynamic class is a child class from BaseAerodynamic. This class
*	calculates aerodynamic forces and moments with tables from DATCOM. Tables of
*	derivative are read in from specific file.
*
*/

#include"Constants.h"
#include"BaseAerodynamic.h"
#include<math.h>

#ifndef DATCOMAERODYNAMIC_H
#define DATCOMAERODYNAMIC_H

class DATCOMAerodymamic : public BaseAerodynamic
{
public:
	/**
	* @brief constructor
	*/
	DATCOMAerodymamic();

	/**
	* @brief destructor
	*/
	~DATCOMAerodymamic();

	/**
	* @brief read in tables of derivatives
	*/
	void initializeAerodynamic();

	/**
	* @brief	current flight state is used to interpolated derivatives
				and  a linear aerodynamic model calculates forces
				and moments
	*/
	void calcAerodynamic(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

private:


};

#endif DATCOMAERODYNAMIC_H
