#include "BaseTrajectory.h"

BaseTrajectory::BaseTrajectory()
{
}

BaseTrajectory::~BaseTrajectory()
{
}

void BaseTrajectory::initTrajectory(AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData,
									AutopilotStruct & AutopilotData,
									GuidanceStruct & GuidanceData)
{
	this->initializeTrajectory(AeroData,
								AirframeData,
								ThrustData,
								AircraftData,
								AutopilotData,
								GuidanceData);
}

void BaseTrajectory::updateTrajectory(Float64 FlightTime, 
									  AtmosphereStruct & AtmoData, 
									  AerodynamicStruct & AeroData,	
									  AirframeStruct & AirframeData, 
									  ThrustStruct & ThrustData, 
									  AutopilotStruct & AutopilotData, 
									  GuidanceStruct & GuidanceData)
{
	this->calcTrajectory(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						AutopilotData,
						GuidanceData);
}


void BaseTrajectory::initializeTrajectory(AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData,
										AircraftStruct &AircraftData, 
										AutopilotStruct & AutopilotData,
										GuidanceStruct & GuidanceData)
{
}

void BaseTrajectory::calcTrajectory(Float64 FlightTime, 
									AtmosphereStruct & AtmoData, 
									AerodynamicStruct & AeroData, 
									AirframeStruct & AirframeData, 
									ThrustStruct & ThrustData, 
									AutopilotStruct & AutopilotData, 
									GuidanceStruct & GuidanceData)
{
}
