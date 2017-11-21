#pragma once
#include"BaseThrust.h"
#include"ThrustAnalytical.h"

class Engine
{
public:
	Engine();

	~Engine();

	void selectEngineType(int type);

	void initEngineType();

	void updateEngine(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

private:
	BaseThrust * BasisThrust;


};