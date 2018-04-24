/**
*	@ingroup IMU
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	falwlessIMU class is a child class of BaseIMU. A flawless IMU
*	is simulated.
*/
#include"BaseIMU.h"

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
	void initIMU();

	/**
	* \brief update flawless IMU
	* @param	FlightTime		flight time
	* @param	AirframeData	structure of Airframe data
	* @param	IMUData	structure of IMU data
	*/
	void updateIMU(Float64 FlightTime, 
					AirframeStruct & AirframeData, 
					IMUStruct &IMUData);

private:

};