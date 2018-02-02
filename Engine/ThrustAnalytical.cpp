#include "ThrustAnalytical.h"

/// constructor
ThrustAnalytical::ThrustAnalytical():BaseThrust()
{
	ReadInThrustData = new readInData;
}

/// destrcutor
ThrustAnalytical::~ThrustAnalytical()
{
}

/// data is read in from Engine.dat and stored in private variables
void ThrustAnalytical::initThrust(ThrustStruct & ThrustData,
										AircraftStruct &AircraftData)
{
	
	ThrustForce.setZero();
	ThrustMoment.setZero();

	EnginePos(0) = ReadInThrustData->readInParameter("x_F", "Engine.dat");
	EnginePos(1) = ReadInThrustData->readInParameter("y_F", "Engine.dat");
	EnginePos(2) = ReadInThrustData->readInParameter("z_F", "Engine.dat");

	maxThrust = ReadInThrustData->readInParameter("F_max", "Engine.dat");
	incidenceAngle = ReadInThrustData->readInParameter("incidenceAngle", "Engine.dat");

	ThrustData.i = incidenceAngle;
	ThrustData.F_max = maxThrust;
	ThrustData.r = EnginePos;
}

/// calculation of thrust forces and moments
void ThrustAnalytical::updateThrust(Float64 FlightTime,
								  AtmosphereStruct & AtmoData,
								  AerodynamicStruct & AeroData,
								  AirframeStruct & AirframeData,
								  ThrustStruct & ThrustData)
{
	std::cout << "Analytische Schubberechnung" << std::endl;
}


