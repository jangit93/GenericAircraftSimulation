#include "Trajectory6DoF.h"

Trajectory6Dof::Trajectory6Dof()
{
	/*
	engine = new Engine;
	aerodynamics = new Aerodynamics;
	airframe = new Airframe*/

}

Trajectory6Dof::~Trajectory6Dof()
{
}
/*
void Trajectory6Dof::initTrajectory(AerodynamicStruct & AeroData,
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

void Trajectory6Dof::updateTrajectory(Float64 FlightTime,
	AtmosphereStruct & AtmoData,
	AerodynamicStruct & AeroData,
	AirframeStruct & AirframeData,
	ThrustStruct & ThrustData,
	AutopilotStruct & AutopilotData,
	GuidanceStruct & GuidanceData)
{


	aerodynamics->updateAerodynamic(FlightTime,
									AtmoData,
									AeroData,
									AirframeData,
									ThrustData);

	engine->updateEngine(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData);

	airframe->updateTranslational(AeroData,
									ThrustData,
									AirframeData);

	airframe->updateRotational(AeroData,
								ThrustData,
								AirframeData);


}
*/