#include "Aerodynamic.h"

Aerodynamics::Aerodynamics()
{
	int a = 1;
	selectAerodynamicType(a);

}

Aerodynamics::~Aerodynamics()
{
}

void Aerodynamics::selectAerodynamicType(int type)
{
	switch (type)
	{
	case 1:
		std::cout << "Aerodynamic:\t" << "DATCOM Aerodynamic" << std::endl;
		aerodynamic = new DATCOMAerodymamic;
		break;
	}
}

void Aerodynamics::initAerodynamic(Float64 &FlightTime, AerodynamicStruct & AeroData,
								   AircraftStruct & AircraftData)
{
	aerodynamic->initAerodynamic(FlightTime, AeroData,
								 AircraftData);
}

void Aerodynamics::updateAerodynamic(Float64 &FlightTime, 
									AtmosphereStruct & AtmoData, 
									AerodynamicStruct & AeroData, 
									AirframeStruct & AirframeData, 
									ThrustStruct & ThrustData)
{

	aerodynamic->updateAerodynamic(FlightTime,
									AtmoData,
									AeroData,
									AirframeData,
									ThrustData);
}

void Aerodynamics::LogAeroData()
{
	aerodynamic->LogAeroData();
}
