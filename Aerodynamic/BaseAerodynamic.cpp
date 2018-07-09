#include "BaseAerodynamic.h"

BaseAerodynamic::BaseAerodynamic()
{
}

BaseAerodynamic::~BaseAerodynamic()
{
}

void BaseAerodynamic::updateAerodynamic(Float64 FlightTime, 
										AtmosphereStruct & AtmoData, 
										AerodynamicStruct & AeroData, 
										AirframeStruct & AirframeData, 
										ThrustStruct & ThrustData, 
										ActuatorStruct &ActuatorData,  
										IMUStruct &IMUData, 
										NavigationStruct  &NavData)
{
	
}



void BaseAerodynamic::initAerodynamic(Float64 &FlightTime, 
									  AerodynamicStruct & AeroData, 
									  AircraftStruct & AircraftData)
{

}

void BaseAerodynamic::LogAeroData()
{
}



