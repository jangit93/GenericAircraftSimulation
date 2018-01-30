#pragma once


#include"BaseIMU.h"

class flawlessIMU : public BaseIMU
{
public:

	flawlessIMU();

	~flawlessIMU();

	void initializeIMU();

	void calcIMU(Float64 FlightTime, AirframeStruct & AirframeData, IMUStruct &IMUData);

private:

};