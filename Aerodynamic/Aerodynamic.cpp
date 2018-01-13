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
		std::cout << "Aerodynamic: DATCOM Aerodynamic" << std::endl;
		aerodynamic = new DATCOMAerodymamic;
		break;
	}
}

void Aerodynamics::initAerodynamic(AerodynamicStruct & AeroData, AircraftStruct & AircraftData)
{
	aerodynamic->initAerodynamic(AeroData, 
								 AircraftData);
}

void Aerodynamics::updateAerodynamic(Float64 FlightTime, 
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
