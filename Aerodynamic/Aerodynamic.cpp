#include "Aerodynamic.h"

Aerodynamics::Aerodynamics()
{
	int a = 2;
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
		aerodynamic = new BaseAerodynamic;
		break;
	case 2:
		std::cout << "Aerodynamic: DATCOM Aerodynamic" << std::endl;
		aerodynamic = new DATCOMAerodymamic;
		break;
	}
}

void Aerodynamics::initAerodynamic()
{
	aerodynamic->initAerodynamic();
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
