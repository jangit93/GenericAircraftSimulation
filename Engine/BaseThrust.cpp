#include "BaseThrust.h"

BaseThrust::BaseThrust()
{
}

BaseThrust::~BaseThrust()
{
}

void BaseThrust::initThrust(ThrustStruct & ThrustData,
							AircraftStruct &AircraftData)
{
	std::cout << "Basis Schubklasse Init" << std::endl;
}






void BaseThrust::updateThrust(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData)
{
	std::cout << "Basis Schubklasse" << std::endl;
}
