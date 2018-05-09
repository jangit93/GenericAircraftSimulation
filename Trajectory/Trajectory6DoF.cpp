#include "Trajectory6DoF.h"

Trajectory6Dof::Trajectory6Dof(SimDPreference &Simpref):Trajectory3Dof(Simpref)
{
	
	airframe = new Airframe;
	guidance = new Guidance(Simpref);
	autopilot = new Autopilot;
	Trafo = new Transformation;

}

Trajectory6Dof::~Trajectory6Dof()
{
}

void Trajectory6Dof::initTrajectory(Float64 FlightTime, 
									AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData,
									GuidanceStruct & GuidanceData,
									NavigationStruct &NavData,
									ActuatorStruct &ActuatorData,
									IMUStruct &IMUData)
{
	initTrajectory6Dof(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData,
						GuidanceData,
						NavData);

	dt = 0.01;
}


void Trajectory6Dof::initTrajectory6Dof(Float64 FlightTime, 
									AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData,
									GuidanceStruct & GuidanceData,
									NavigationStruct &NavData)
{
	
	initTrajectory3DoF(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData);

	autopilot->initAutopilot();

	guidance->initGuidance(FlightTime,GuidanceData,AircraftData);
	
}

void Trajectory6Dof::updateTrajectory(Float64 FlightTime, 
									  AtmosphereStruct & AtmoData,
									  AerodynamicStruct & AeroData, 
									  AirframeStruct & AirframeData, 
									  ThrustStruct & ThrustData, 
									  GuidanceStruct & GuidanceData, 
									  NavigationStruct & NavData, 
									  ActuatorStruct & ActuatorData, 
									  IMUStruct & IMUData)
{

	integrationTrajectory(AirframeData);

	updateTrajectory6Dof(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						GuidanceData,
						NavData);
}

void Trajectory6Dof::updateTrajectory6Dof(Float64 FlightTime,
										AtmosphereStruct & AtmoData,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData,
										GuidanceStruct & GuidanceData,
										NavigationStruct &NavData)
{

	

	updateTrajectory3DoF(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData);

	airframe->updateRotational(AeroData,
								ThrustData,
								AirframeData);

	guidance->updateGuidance(FlightTime,
							AeroData,
							ThrustData,
							AirframeData,
							GuidanceData);

	autopilot->updateAutopilot(FlightTime,
							   AirframeData,
							   AeroData,
							   GuidanceData);

	log6DofData();


}

void Trajectory6Dof::integrationTrajectory(AirframeStruct & AirframeData)
{
	AirframeData.velNED = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, dt);
	AirframeData.posNED = EulerIntegration(AirframeData.posNED, AirframeData.velNED, dt);

	AirframeData.rotRatesBody = EulerIntegration(AirframeData.rotRatesBody, AirframeData.accRotBody, dt);
	AirframeData.EulerAngles = EulerIntegration(AirframeData.EulerAngles, AirframeData.Eulerdot, dt);

	AirframeData.Gamma = atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(1)*AirframeData.velNED(1)));


	AirframeData.Chi = atan2(AirframeData.velNED(1), AirframeData.velNED(0));

	AirframeData.matNEDToBody = Trafo->MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo->MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);

}


void Trajectory6Dof::log6DofData()
{
	guidance->logGuidanceData();

	log3DofData();
}

