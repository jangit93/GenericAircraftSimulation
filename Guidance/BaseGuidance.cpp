#include "BaseGuidance.h"

BaseGuidance::BaseGuidance()
{
}

BaseGuidance::~BaseGuidance()
{
}

void BaseGuidance::initGuidance()
{
	this->initializeGuidance();
}

void BaseGuidance::updateGuidance(Float64 FlightTime, 
								  AerodynamicStruct & AeroData, 
								  ThrustStruct & ThrustData, 
								  AircraftStruct & AircraftData, 
								  AirframeStruct & AirframeData, 
								  AtmosphereStruct & AtmosphereData,
								  GuidanceStruct &GuidanceData)
{
	this->calcGuidance(FlightTime,
						AeroData,
						ThrustData,
						AircraftData,
						AirframeData,
						AtmosphereData,
						GuidanceData);
}

void BaseGuidance::initializeGuidance()
{
}

void BaseGuidance::calcGuidance(Float64 FlightTime, 
								AerodynamicStruct & AeroData, 
								ThrustStruct & ThrustData, 
								AircraftStruct & AircraftData, 
								AirframeStruct & AirframeData, 
								AtmosphereStruct & AtmosphereData,
								GuidanceStruct &GuidanceData)
{
}
