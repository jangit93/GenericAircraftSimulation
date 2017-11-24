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
	this->calcAerodynamic(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData);
}

void BaseAerodynamic::initAerodynamic()
{
	this->initializeAerodynamic();
}

void BaseAerodynamic::calcAerodynamic(Float64 FlightTime,
									  AtmosphereStruct & AtmoData, 
									  AerodynamicStruct & AeroData,
									  AirframeStruct & AirframeData,
									  ThrustStruct & ThrustData)
{
	std::cout << "Base Aerodynamic Update" << std::endl;
}

void BaseAerodynamic::initializeAerodynamic()
{
	std::cout << "Base Aerodynamic Init" << std::endl;
}
