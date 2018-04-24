#include "Engine.h"

Engine::Engine(SimDPreference &SimPref)
{
	selectEngineType(SimPref.EngineMode);
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

void Engine::initEngine(Float64 &FlightTime,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData)
			
{
	Thrust->initThrust(FlightTime,
						ThrustData,
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

void Engine::logEngineData()
{
	Thrust->logEngineData();
}
