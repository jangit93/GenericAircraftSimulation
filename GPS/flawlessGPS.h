/**
*	@ingroup GPS
*	@author Jan Olucak
*	@date 01.05.2018
*	@version 1.0
*
*	flawlessGPS class is a child class of BaseGPS class. A flawless GPS-module is
*	simulated.
*
*/

#ifndef FLAWLESSGPS_H
#define FLAWLESSGPS_H


#include"BaseGPS.h"

class flawlessGPS : public BaseGPS
{
public:
	/**
	* \brief constructor
	*/
	flawlessGPS();

	/**
	* \brief destructor
	*/
	~flawlessGPS();

	/**
	* \brief initialize flawless GPS
	*/
	void initGPS();


	/**
	* \brief update flwaless GPS 
	*	@param	FlightTime	 flighttime
	*	@param	NavData		 structure of navigation data
	*	@param	AirframeData structure of flight states
	*/
	void updateGPS(Float64 FlightTime, 
				   NavigationStruct &NavData,
				   AirframeStruct & AirframeData);


	/**
	* \brief define GPS data output
	*/
	void initlogGPSData();

	/**
	* \brief log GPS data
	*/
	void logGPSData();

private:

};
#endif // !FLAWLESSGPS_H