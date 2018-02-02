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
										ThrustStruct & ThrustData)
{
	std::cout << "Base Aerodynamic Update" << std::endl;
}



void BaseAerodynamic::initAerodynamic(AerodynamicStruct & AeroData, AircraftStruct & AircraftData)
{
	std::cout << "Base Aerodynamic Init" << std::endl;
}



