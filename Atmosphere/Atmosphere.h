/** @defgroup	Atmosphere Atmosphere
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Atmosphere class simulates the US Standard atmosphere.  Air density, speed of sound, temperature
*   and pressure are calculated depending on altitude.
*  @{
*/

#ifndef ATMOSPHERE__HPP
#define ATMOSPHERE__HPP

#include <math.h>
#include <iostream>
#include"Constants.h"
#include"DataCloud.h"
#include"IndependetDataTypes.h"

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
	*	@param	Altitude	current altitude
	*	@param	AtmoData	store air density, speed of sound, temperature, pressure
	*/
	void	updateAtmosphere(Float64 &Altitude, 
							 AtmosphereStruct &AtmoData);

private:
	Float64	Temperature;	
	Float64 Pressure;       
	Float64	rho;		
	Float64 speedOfSound;   
	Float64 Alt;
};
/**@}*/
#endif	ATMOSPHERE__HPP
