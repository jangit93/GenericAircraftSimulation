#include "flawlessGPS.h"

flawlessGPS::flawlessGPS()
{
}

flawlessGPS::~flawlessGPS()
{
}

void flawlessGPS::initializeGPS()
{
}

void flawlessGPS::calcGPS(Float64 FlightTime, NavigationStruct & NavData)
{
	NavData.realPOS = NavData.intPOS;
	NavData.realVelocity = NavData.intVelocity;
}
