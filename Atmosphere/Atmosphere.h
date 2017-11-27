/** @defgroup	Atmosphere Atmosphere
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	DataCloud is a global data storage for structures. It serves the purpose to provide data
*	for several applications like the simulation itself, module and unit tests.
*  @{
*/

#ifndef ATMOSPHERE__HPP
#define ATMOSPHERE__HPP

#include <math.h>
#include <iostream>
#include"../Tools/Constants.h"
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"

class Atmopshere
{
public:

	/**
	* \brief constructor
	*/
	Atmopshere();

	/**
	* \brief destructor
	*/
	~Atmopshere();

	/**
	* \brief initialize atmospheric paramters
	*/
	void	initAtmosphere();

	/**
	* \brief calculates atmospheric data depending on altitude
	*	@param	Altitude			current altitude
	*	@return	AtmosphericStruc	store air density, speed of sound, temperature, pressure
	*/
	void	updateAtmosphere(Float64 &Altitude, AtmosphereStruct &AtmoData);

private:
	Float64	Temperature;	// [K]
	Float64 Pressure;       //[Pa]
	Float64	rho;			//[Kg / m³]
	Float64 speedOfSound;   //[m / s]
	
	AtmosphereStruct AtmosphereData;

};
/**@}*/
#endif	ATMOSPHERE__HPP
