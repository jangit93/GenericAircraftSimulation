#include "Engine.h"

Engine::Engine()
{
	int a = 1;
	selectEngineType(a);
}

Engine::~Engine()
{
}

void Engine::selectEngineType(int type)
{
	switch (type)
	{
	case 1:
		std::cout << "Thrust:\t\t" << "Analytical Thrust" << std::endl;
		Thrust = new ThrustAnalytical;
		break;
	}
}

void Engine::initEngine(ThrustStruct & ThrustData,
						AircraftStruct &AircraftData)
			
{
	Thrust->initThrust(ThrustData,
					   AircraftData);
}

void Engine::updateEngine(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData)
{
	Thrust->updateThrust(FlightTime,
						 AtmoData,
						 AeroData,
						 AirframeData,
						 ThrustData);
}
