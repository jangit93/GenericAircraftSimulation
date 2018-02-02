#pragma once


#include"BaseIMU.h"

class flawlessIMU : public BaseIMU
{
public:

	flawlessIMU();

	~flawlessIMU();

	void initIMU();

	void updateIMU(Float64 FlightTime, AirframeStruct & AirframeData, IMUStruct &IMUData);

private:

};