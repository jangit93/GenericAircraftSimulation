#include "ThrustAnalytical.h"

ThrustAnalytical::ThrustAnalytical():BaseThrust()
{
	ReadInThrustData = new readInData;
}

ThrustAnalytical::~ThrustAnalytical()
{
}

void ThrustAnalytical::initializeThrust()
{
	//std::cout << "Analytische Schubberechnung Init" << std::endl;
	ThrustForce.setZero();
	ThrustMoment.setZero();

	EnginePos(0) = ReadInThrustData->readInParameter("x_F", "Engine.dat");
	EnginePos(1) = ReadInThrustData->readInParameter("y_F", "Engine.dat");
	EnginePos(2) = ReadInThrustData->readInParameter("z_F", "Engine.dat");

	maxThrust = ReadInThrustData->readInParameter("F_max", "Engine.dat");
	incidenceAngle = ReadInThrustData->readInParameter("incidenceAngle", "Engine.dat");
}


void ThrustAnalytical::calcThrust(Float64 FlightTime,
								  AtmosphereStruct & AtmoData,
								  AerodynamicStruct & AeroData,
								  AirframeStruct & AirframeData,
								  ThrustStruct & ThrustData)
{
	//std::cout << "Analytische Schubberechnung" << std::endl;
	std::cout << EnginePos << std::endl;
	std:: cout << maxThrust <<  std::endl;
}


