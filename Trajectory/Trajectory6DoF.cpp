#include "Trajectory6DoF.h"

Trajectory6Dof::Trajectory6Dof() 
{
	
	airframe = new Airframe;
	guidance = new Guidance;
	autopilot = new Autopilot;

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

	guidance->initGuidance();
	
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

	autopilot->updateAutopilot();



}

