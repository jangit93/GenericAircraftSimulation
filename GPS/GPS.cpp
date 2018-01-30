#include "GPS.h"

GPS::GPS()
{
	int Type =2 ;
	selectGPS(Type);
}

GPS::~GPS()
{
}

void GPS::selectGPS(int Type)
{
	switch (Type)
	{
	case 1:
		gps = new BaseGPS;
		break;
	case 2:
		gps = new flawlessGPS;
	}
}

void GPS::initGPS()
{
	gps->initGPS();
}

void GPS::updateGPS(Float64 FlightTime, NavigationStruct & NavData)
{
	gps->updateGPS(FlightTime, NavData);
}
