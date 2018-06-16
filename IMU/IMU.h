/** @defgroup	IMU IMU
*	@author		Jan Olucak
*	@date		02.01.2018
*	@version	1.0
*
*	IMU class is used to call the desired IMU model. The IMU model is selected from
*	General.dat input file.
*  @{
*/

#ifndef IMU_H
#define IMU_H

#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseIMU.h"
#include"flawlessIMU.h"

class IMU
{
public:
	/**
	* \brief constructor
	*	@param	SimPref	 structure of model selctions
	*/
	IMU(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~IMU();


	/**
	* \brief set pointer to desired class
	*	@param	Type	Aerodynamic Model Selection
	*/
	void selectIMU(int Type);

	/**
	* \brief call to desired init-function
	*/
	void initIMU(IMUStruct & IMUData);


	/**
	* \brief call to desired update function
	*	@param	FlightTime			flighttime
	*	@param	AirframeData		structure of airframe data
	*	@param	IMUData				structure of IMU data
	*/
	void updateIMU(Float64 FlightTime, 
				   AirframeStruct & AirframeData, 
				   IMUStruct &IMUData);

	/**
	* \brief log IMU data
	*/
	void logIMUData();

private:
	BaseIMU * imu;
};
/**@}*/
#endif // !IMU_H