/** @defgroup	GPS GPS
*	@author		Jan Olucak
*	@date		02.01.2018
*	@version	1.0
*
*	GPS class is used to call the desired GPS model. The GPS model is selected from
*	General.dat input file.
*  @{
*/

#ifndef GPS_H
#define GPS_H

#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseGPS.h"
#include"flawlessGPS.h"

class GPS
{
public:
	/**
	* \brief constructor
	*	@param	SimPref	 structure of model selctions
	*/
	GPS(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~GPS();

	/**
	* \brief set pointer to desired class
	*	@param	Type	Aerodynamic Model Selection
	*/
	void selectGPS(int Type);

	/**
	* \brief call to desired init-function
	*/
	void initGPS();

	/**
	* \brief call to desired update function 
	*	@param	FlightTime	flighttime
	*	@param	NavData		structure of navigation data
	*/
	void updateGPS(Float64 FlightTime,
					NavigationStruct & NavData, 
					AirframeStruct & AirframeData);

	/**
	* \brief log GPS data
	*/
	void logGPSData();

private:
	BaseGPS * gps;
};
/**@}*/
#endif GPS_H