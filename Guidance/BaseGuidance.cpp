#include "BaseGuidance.h"

BaseGuidance::BaseGuidance()
{
}

BaseGuidance::~BaseGuidance()
{
}

void BaseGuidance::initGuidance(Float64 &FlightTime, GuidanceStruct &GuidanceData, AircraftStruct &AircraftData)
{
	
}

void BaseGuidance::updateGuidance(Float64 FlightTime, 
								  AerodynamicStruct & AeroData, 
								  ThrustStruct & ThrustData, 
								  AirframeStruct & AirframeData, 
								  GuidanceStruct &GuidanceData)
{

}

void BaseGuidance::initLogGuidance(Float64 FlightTime, 
								   GuidanceStruct & GuidanceData)
{
}

void BaseGuidance::logGuidanceData()
{
}
