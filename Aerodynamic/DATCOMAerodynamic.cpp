#include "DATCOMAerodynamic.h"

DATCOMAerodymamic::DATCOMAerodymamic()
{
}

DATCOMAerodymamic::~DATCOMAerodymamic()
{
}

void DATCOMAerodymamic::initializeAerodynamic(AerodynamicStruct & AeroData,
											  AircraftStruct & AircraftData)
{
	std::cout << "DATCOM Aerodynamic Init" << std::endl;
}

void DATCOMAerodymamic::calcAerodynamic(Float64 FlightTime,
										AtmosphereStruct & AtmoData,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData)
{
	std::cout << "DATCOM Aerodynamic Update" << std::endl;
}
