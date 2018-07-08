#include "Trajectory3DoF.h"

Trajectory3Dof::Trajectory3Dof(SimDPreference &SimPref)
{
	engine		 = new Engine(SimPref);
	aerodynamics = new Aerodynamics(SimPref);
	airframe     = new Airframe;

	dt = SimPref.dt;
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

	Transformation Trafo;
	AirframeData.matNEDToBody = Trafo.MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo.MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo.MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);

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

	AirframeData.velNED = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, dt);
	AirframeData.posNED = EulerIntegration(AirframeData.posNED, AirframeData.velNED, dt);

	IMUData.accTransNED = AirframeData.accTransNED;

	NavData.absVel = AirframeData.velBody.norm();
	NavData.velNED = AirframeData.velNED;
	NavData.posNED = AirframeData.posNED;

	AirframeData.Gamma = atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(1)*AirframeData.velNED(1)));
	AirframeData.Chi = atan2(AirframeData.velNED(1), AirframeData.velNED(0));



	updateTrajectory3DoF(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						ActuatorData,
						IMUData,
						NavData);
		
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
										  ThrustStruct & ThrustData,
										  ActuatorStruct &ActuatorData,
										  IMUStruct &IMUData,
										  NavigationStruct  &NavData)
{
	aerodynamics->updateAerodynamic(FlightTime,
									AtmoData,
									AeroData,
									AirframeData,
									ThrustData,
									ActuatorData,
									IMUData,
									NavData);

	engine->updateEngine(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						ActuatorData);

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
