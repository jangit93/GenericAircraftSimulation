/**
*	@ingroup IMU
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	BaseIMU class is the superclass for all GPS models. Using pointer to base
*	init and update function allows the user to extend the IMU module with new
*	models.
*
*/

#ifndef BASEIMU_H
#define BASEIMU_H



#include"../DataCloud/DataCloud.h"


class BaseIMU
{
public:
	/**
	* \brief constructor
	*/
	BaseIMU();

	/**
	* \brief destructor
	*/
	~BaseIMU();


	/**
	* \brief initialize IMU
	*/
    virtual void initIMU();

	/**
	* \brief update IMU
	* @param	FlightTime		flight time
	* @param	AirframeData	structure of Airframe data
	* @param	IMUData	structure of IMU data
	*/
	virtual void updateIMU(Float64 Flighttime, 
						   AirframeStruct & AirframeData,
						   IMUStruct &IMUData);



private:
};
#endif // !BASEIMU_H