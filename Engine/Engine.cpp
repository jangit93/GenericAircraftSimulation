#include "Engine.h"

Engine::Engine()
{
	int a = 2;
	selectEngineType(a);

	initEngineType();
}

Engine::~Engine()
{
}

void Engine::selectEngineType(int type)
{
	switch (type)
	{
	case 1:
		BasisThrust = new BaseThrust; 
		break;
	case 2:
		BasisThrust = new ThrustAnalytical;
		break;
	}
}

void Engine::initEngineType()
{
	BasisThrust->initThrust();
}

void Engine::updateEngine(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData)
{
	BasisThrust->updateThrust(FlightTime,
							  AtmoData,
							  AeroData,
							  AirframeData,
							  ThrustData);
}
