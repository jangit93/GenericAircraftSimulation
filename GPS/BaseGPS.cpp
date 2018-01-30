#include "BaseGPS.h"

BaseGPS::BaseGPS()
{
}

BaseGPS::~BaseGPS()
{
}

void BaseGPS::initGPS()
{
	this->initializeGPS();
}

void BaseGPS::initializeGPS()
{
}

void BaseGPS::updateGPS(Float64 Flighttime, NavigationStruct & NavData)
{
	this->calcGPS(Flighttime, NavData);
}

void BaseGPS::calcGPS(Float64 Flighttime, NavigationStruct & NavData)
{
}
