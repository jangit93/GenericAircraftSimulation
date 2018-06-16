/**
*	@ingroup IMU
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	falwlessIMU class is a child class of BaseIMU. A flawless IMU 
*	is simulated.
*/

#ifndef FLAWLESSIMU_H
#define FLAWLESSIMU_H


#include"BaseIMU.h"
#include"ODESolver.cpp"
#include"DataLogger.h"

class flawlessIMU : public BaseIMU
{
public:
	/**
	* \brief constructor
	*/
	flawlessIMU();

	/**
	* \brief destructor
	*/
	~flawlessIMU();


	/**
	* \brief initialize flawless IMU
	*/
	void initIMU(IMUStruct & IMUData);

	/**
	* \brief update flawless IMU
	* @param	FlightTime		flight time
	* @param	AirframeData	structure of Airframe data
	* @param	IMUData	structure of IMU data
	*/
	void updateIMU(Float64 FlightTime, 
					AirframeStruct & AirframeData, 
					IMUStruct &IMUData);


	/**
	* \brief define IMU data output
	* @param FlightTime time of flight
	* @param IMUDaa structure with accelerations and rotatory rates
	*/
	void initlogIMUData(Float64 &FlightTime,
						IMUStruct &IMUData);

	/**
	* \brief log IMU data
	*/
	void logIMUData();

private:
	DataLogger * logimuData;
};
#endif // !FLAWLESSIMU_H