#include "ThrustAnalytical.h"

ThrustAnalytical::ThrustAnalytical():BaseThrust()
{
	initThrust();

}

ThrustAnalytical::~ThrustAnalytical()
{
}

void ThrustAnalytical::initThrust()
{
	ThrustForce.setZero();
	ThrustMoment.setZero();

	readInData *ReadInThrustData = new readInData;
	EnginePos(0) = ReadInThrustData->readInParameter("x_F", "Engine.dat");
	EnginePos(1) = ReadInThrustData->readInParameter("y_F", "Engine.dat");
	EnginePos(2) = ReadInThrustData->readInParameter("z_F", "Engine.dat");

	maxThrust	   = ReadInThrustData->readInParameter("F_max", "Engine.dat");
	incidenceAngle = ReadInThrustData->readInParameter("incidenceAngle", "Engine.dat");
}

void ThrustAnalytical::updateThrust(Float64 FlightTime,
									AtmosphereStruct & AtmoData,
									AerodynamicStruct & AeroData, 
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData)
{
	rho = AtmoData.rho;
	Mach = AeroData.VelAero;
	StickPosition = AirframeData.StickPosition;

	absThrust = StickPosition*maxThrust*(rho / rho_0)*(1 + Kt*Mach);

	ThrustForce(0, 0) = absThrust*cos(incidenceAngle);
	ThrustForce(1, 1) = 0;
	ThrustForce(2, 2) = absThrust*sin(incidenceAngle);

	ThrustMoment(0, 0) = absThrust*sin(incidenceAngle)*EnginePos(1);
	ThrustMoment(1, 1) = absThrust*(cos(incidenceAngle)*EnginePos(2) - sin(incidenceAngle)*EnginePos(0));
	ThrustMoment(2, 2) = -absThrust*cos(incidenceAngle)*EnginePos(1);

	ThrustData.ThrustForce   = ThrustForce;
	ThrustData.ThrustMoments = ThrustMoment;
}

