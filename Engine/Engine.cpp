#include "Engine.h"

Engine::Engine()
{
	int a = 2;
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
		Thrust = new BaseThrust; 
		break;
	case 2:
		std::cout << "Thrust:" << "Analytical Thrust" << std::endl;
		Thrust = new ThrustAnalytical;
		break;
	}
}

void Engine::initEngine()
{
	Thrust->initThrust();
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
