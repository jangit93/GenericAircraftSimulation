#include "Trajectory3DoF.h"

Trajectory3Dof::Trajectory3Dof(SimDPreference &SimPref)
{
	engine		 = new Engine(SimPref);
	aerodynamics = new Aerodynamics(SimPref);
	airframe     = new Airframe;

}

Trajectory3Dof::~Trajectory3Dof()
{
}

void Trajectory3Dof::initTrajectory(Float64 &FlightTime, 
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
						ThrustData,ActuatorData);
		
}

void Trajectory3Dof::initTrajectory3DoF(Float64 &FlightTime,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData, 
										ThrustStruct & ThrustData, 
										AircraftStruct & AircraftData)
{

	airframe->initAirframe(FlightTime,
						   AircraftData,
						   AirframeData);

	engine->initEngine(FlightTime,
					   ThrustData,
					   AircraftData);

	aerodynamics->initAerodynamic(FlightTime, 
								  AeroData,
								  AircraftData);
}

void Trajectory3Dof::updateTrajectory3DoF(Float64 FlightTime, 
										  AtmosphereStruct & AtmoData, 
										  AerodynamicStruct & AeroData, 
										  AirframeStruct & AirframeData, 
										  ThrustStruct & ThrustData, ActuatorStruct &ActuatorData)
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

	//log3DofData();

}

void Trajectory3Dof::log3DofData()
{
	aerodynamics->LogAeroData();
	engine->logEngineData();
	airframe->logAirframeData();
}
