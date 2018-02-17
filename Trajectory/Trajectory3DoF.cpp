#include "Trajectory3DoF.h"

Trajectory3Dof::Trajectory3Dof()
{
	engine		 = new Engine;
	aerodynamics = new Aerodynamics;
	airframe     = new Airframe;

}

Trajectory3Dof::~Trajectory3Dof()
{
}

void Trajectory3Dof::initTrajectory(Float64 FlightTime, 
									AerodynamicStruct & AeroData,
										  AirframeStruct & AirframeData,
										  ThrustStruct & ThrustData,
										  AircraftStruct &AircraftData,
										  GuidanceStruct & GuidanceData,
										NavigationStruct &NavData,
										ActuatorStruct &ActuatorData,
										IMUStruct &IMUData)
{
	initTrajectory3DoF(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData);

}

void Trajectory3Dof::updateTrajectory(Float64 FlightTime,
									AtmosphereStruct & AtmoData,
									AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									GuidanceStruct & GuidanceData,
									NavigationStruct &NavData,
									ActuatorStruct &ActuatorData,
									IMUStruct &IMUData)
{

	updateTrajectory3DoF(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData);
		
}

void Trajectory3Dof::initTrajectory3DoF(Float64 FlightTime,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData, 
										ThrustStruct & ThrustData, 
										AircraftStruct & AircraftData)
{
	airframe->initAirframe(AircraftData,
		AirframeData);

	engine->initEngine(ThrustData,
		AircraftData);

	aerodynamics->initAerodynamic(FlightTime, AeroData,
		AircraftData);
}

void Trajectory3Dof::updateTrajectory3DoF(Float64 FlightTime, 
										  AtmosphereStruct & AtmoData, 
										  AerodynamicStruct & AeroData, 
										  AirframeStruct & AirframeData, 
										  ThrustStruct & ThrustData)
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

	logData(FlightTime, 
			AtmoData, 
			AeroData, 
			AirframeData, 
			ThrustData);

}

void Trajectory3Dof::logData(Float64 FlightTime, 
							 AtmosphereStruct & AtmoData, 
							 AerodynamicStruct & AeroData, 
							 AirframeStruct & AirframeData, 
							 ThrustStruct & ThrustData)
{
	aerodynamics->LogAeroData();
}
