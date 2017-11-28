#include "BaseTrajectory.h"

BaseTrajectory::BaseTrajectory()
{
}

BaseTrajectory::~BaseTrajectory()
{
}

void BaseTrajectory::initTrajectory()
{
	this->initializeTrajectory();
}

void BaseTrajectory::updateTrajectory(Float64 FlightTime, 
									  AtmosphereStruct & AtmoData, 
									  AerodynamicStruct & AeroData, 
									  AirframeStruct & AirframeData, 
									  ThrustStruct & ThrustData)
{
	this->calcTrajectory(FlightTime,
		AtmoData,
		AeroData,
		AirframeData,
		ThrustData);
}


void BaseTrajectory::initializeTrajectory()
{
}

void BaseTrajectory::calcTrajectory(Float64 FlightTime,
									AtmosphereStruct & AtmoData,
									AerodynamicStruct & AeroData, 
									AirframeStruct & AirframeData, 
									ThrustStruct & ThrustData)
{
}

