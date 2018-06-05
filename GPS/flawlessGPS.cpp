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
	NavData.realPOS = NavData.intPOS;
	NavData.realVelocity = NavData.intVelocity;
}
