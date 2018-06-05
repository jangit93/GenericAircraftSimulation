#include "GPS.h"

GPS::GPS(SimDPreference &SimPref)
{
	selectGPS(SimPref.GPSMode);
}

GPS::~GPS()
{
}

void GPS::selectGPS(int Type)
{
	switch (Type)
	{
	case 1:
		std::cout << "GPS:\t" << "flawless GPS" << std::endl;
		gps = new flawlessGPS;
	}
}

void GPS::initGPS()
{
	gps->initGPS();
}

void GPS::updateGPS(Float64 FlightTime, 
					NavigationStruct & NavData, 
					AirframeStruct & AirframeData)
{
	gps->updateGPS(FlightTime, NavData,AirframeData);
}
