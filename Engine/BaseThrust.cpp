#include "BaseThrust.h"

BaseThrust::BaseThrust()
{
}

BaseThrust::~BaseThrust()
{
}

void BaseThrust::initThrust()
{
	this->initializeThrust();
}

void BaseThrust::initializeThrust()
{
	std::cout << "Basis Schubklasse Init" << std::endl;
}

void BaseThrust::calcThrust(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData)
{
	std::cout << "Basis Schubklasse" << std::endl;
}


void BaseThrust::updateThrust(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData)
{
	this->calcThrust(FlightTime,
					AtmoData,
					AeroData,
					AirframeData,
					ThrustData);
}
