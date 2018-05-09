#include "BaseTrajectory.h"

BaseTrajectory::BaseTrajectory()
{
}

BaseTrajectory::~BaseTrajectory()
{
}

void BaseTrajectory::initTrajectory(Float64 FlightTime, 
									AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData,
									GuidanceStruct & GuidanceData,
									NavigationStruct &NavData,
									ActuatorStruct &ActuatorData,
									IMUStruct &IMUData)
{

}

void BaseTrajectory::updateTrajectory(Float64 FlightTime, 
									  AtmosphereStruct & AtmoData, 
									  AerodynamicStruct & AeroData,	
									  AirframeStruct & AirframeData, 
									  ThrustStruct & ThrustData,
									  GuidanceStruct & GuidanceData,
										NavigationStruct &NavData,
										ActuatorStruct &ActuatorData,
										IMUStruct &IMUData)
{

}

void BaseTrajectory::logTraj()
{
}


