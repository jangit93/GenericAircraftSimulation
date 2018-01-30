#include "flawlessIMU.h"

flawlessIMU::flawlessIMU()
{
}

flawlessIMU::~flawlessIMU()
{
}

void flawlessIMU::initializeIMU()
{
}

void flawlessIMU::calcIMU(Float64 FlightTime, AirframeStruct & AirframeData, IMUStruct & IMUData)
{
	IMUData.realTRotAcc  = AirframeData.accRotBody;
	IMUData.realTransAcc = AirframeData.accTransBody;
}
