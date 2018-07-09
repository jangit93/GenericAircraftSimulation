#include "Aerodynamic.h"

Aerodynamics::Aerodynamics(SimDPreference &SimPref)
{ 
	selectAerodynamicType(SimPref.AeroMode);

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

void Aerodynamics::initAerodynamic(Float64 &FlightTime, 
								   AerodynamicStruct & AeroData,
								   AircraftStruct & AircraftData)
{
	aerodynamic->initAerodynamic(FlightTime,
								 AeroData,
								 AircraftData);
}

void Aerodynamics::updateAerodynamic(Float64 FlightTime, 
									 AtmosphereStruct & AtmoData, 
									 AerodynamicStruct & AeroData, 
									 AirframeStruct & AirframeData, 
									 ThrustStruct & ThrustData, 
									 ActuatorStruct &ActuatorData,
									 IMUStruct &IMUData, 
									 NavigationStruct  &NavData)
{

	aerodynamic->updateAerodynamic(FlightTime,
								   AtmoData,
								   AeroData,
								   AirframeData,
								   ThrustData,
								   ActuatorData,
								   IMUData,
								   NavData);
}

void Aerodynamics::LogAeroData()
{
	aerodynamic->LogAeroData();
}
