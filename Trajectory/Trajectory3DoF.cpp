#include "Trajectory3DoF.h"

Trajectory3Dof::Trajectory3Dof()
{
	engine = new Engine;
	aerodynamics = new Aerodynamics;
	airframe = new Airframe;

}

Trajectory3Dof::~Trajectory3Dof()
{
}

void Trajectory3Dof::initializeTrajectory(AerodynamicStruct & AeroData,
										  AirframeStruct & AirframeData,
										  ThrustStruct & ThrustData,
										  AircraftStruct &AircraftData,
										 AutopilotStruct & AutopilotData,
										 GuidanceStruct & GuidanceData)
{
	airframe->initAirframe(AircraftData, 
						   AirframeData);

	engine->initEngine(ThrustData,
					   AircraftData);

	aerodynamics->initAerodynamic(AeroData,
								  AircraftData);

	std::cout << "init 3Dof Trajectory" << std::endl;
}

void Trajectory3Dof::calcTrajectorythis(Float64 FlightTime,	
										AtmosphereStruct & AtmoData, 
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData, 
										ThrustStruct & ThrustData,
										AutopilotStruct & AutopilotData,
										GuidanceStruct & GuidanceData)
{
	std::cout << "update 3Dof Trajectory" << std::endl;
}


