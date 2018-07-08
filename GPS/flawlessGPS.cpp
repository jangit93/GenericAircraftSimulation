#include "flawlessGPS.h"

flawlessGPS::flawlessGPS()
{
}

flawlessGPS::~flawlessGPS()
{
}

void flawlessGPS::initGPS()
{
}

void flawlessGPS::updateGPS(Float64 FlightTime, 
							NavigationStruct & NavData,
							AirframeStruct & AirframeData)
{
	NavData.velNED = NavData.velNED;
	NavData.posNED = NavData.posNED;
}

void flawlessGPS::initlogGPSData()
{
}

void flawlessGPS::logGPSData()
{
}
