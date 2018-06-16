/**
*	@ingroup GPS
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	BaseGPS class is the superclass for all GPS models. Using pointer to base
*	init and update function allows the user to extend the GPS module with new
*	models.
*
*/

#ifndef BASEGPS_H
#define BASEGPS_H




#include"../DataCloud/DataCloud.h"

class BaseGPS
{
public:
	/**
	* \brief constructor
	*/
	BaseGPS();

	/**
	* \brief destructor
	*/
	~BaseGPS();

	/**
	* \brief initialize GPS
	*/
	virtual void initGPS();

	/**
	* \brief update GPS data 
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*/
	virtual void updateGPS(Float64 FlightTime, 
						   NavigationStruct &NavData,
						   AirframeStruct & AirframeData);

	/**
	* \brief log GPS data
	*/
	virtual void logGPSData();

private:

};
#endif BASEGPS_H