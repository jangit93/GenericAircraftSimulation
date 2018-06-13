#include "ThrustAnalytical.h"

/// constructor
ThrustAnalytical::ThrustAnalytical():BaseThrust()
{
	ReadInThrustData = new readInData;

	LogEngineData = new DataLogger("EngineData.txt", 25, " ");
}

/// destrcutor
ThrustAnalytical::~ThrustAnalytical()
{
}

/// data is read in from Engine.dat and stored in private variables
void ThrustAnalytical::initThrust(Float64 &FlightTime,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData)
{
	ThrustData.ThrustForce.setZero();
	ThrustData.ThrustMoments.setZero();
	
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
	Kt = 0.7;

	initLogEngineData(FlightTime, ThrustData);
}

// calculation of thrust forces and moments
void ThrustAnalytical::updateThrust(Float64 FlightTime,
								  AtmosphereStruct & AtmoData,
								  AerodynamicStruct & AeroData,
								  AirframeStruct & AirframeData,
								  ThrustStruct & ThrustData, ActuatorStruct& ActuatorData)
{

	                                              
	Float64	T = ActuatorData.Delta* maxThrust* (AtmoData.rho / RHO_0)* (1 + Kt * AeroData.Mach);

	
		ThrustData.ThrustForce(0) = T * cos(incidenceAngle);
		ThrustData.ThrustForce(1) = 0;
		ThrustData.ThrustForce(2) = T * sin(incidenceAngle);

	
		ThrustData.ThrustMoments(0) = T * sin(incidenceAngle) * EnginePos(1);
		ThrustData.ThrustMoments(0) = T * (cos(incidenceAngle) * EnginePos(2) - sin(incidenceAngle)*EnginePos(0));
		ThrustData.ThrustMoments(0) = -T * cos(incidenceAngle) * EnginePos(1);

}

void ThrustAnalytical::initLogEngineData(Float64 & FlightTime, ThrustStruct & ThrustData)
{
	LogEngineData->add("FlightTime [s]", FlightTime);
	LogEngineData->add("F_x", ThrustData.ThrustForce(0));
	LogEngineData->add("F_y", ThrustData.ThrustForce(1));
	LogEngineData->add("F_z", ThrustData.ThrustForce(2));
	LogEngineData->add("M_x", ThrustData.ThrustMoments(0));
	LogEngineData->add("M_x", ThrustData.ThrustMoments(0));
	LogEngineData->add("M_y", ThrustData.ThrustMoments(1));
	LogEngineData->add("M_z", ThrustData.ThrustMoments(2));

	LogEngineData->printHeader();
}

void ThrustAnalytical::logEngineData()
{
	LogEngineData->print();
}


