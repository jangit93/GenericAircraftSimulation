#include "flawlessIMU.h"

flawlessIMU::flawlessIMU()
{
}

flawlessIMU::~flawlessIMU()
{
}

void flawlessIMU::initIMU()
{
}

void flawlessIMU::updateIMU(Float64 FlightTime, 
							AirframeStruct & AirframeData, 
							IMUStruct & IMUData)
{
	IMUData.realTRotAcc  = AirframeData.accRotBody;
	IMUData.realTransAcc = AirframeData.accTransBody;
	
	IMUData.rotRatesBody = EulerIntegration(IMUData.rotRatesBody, IMUData.realTRotAcc, IMUData.dt);
	AirframeData.rotRatesBody = IMUData.rotRatesBody;
}
