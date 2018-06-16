#include "RealSystemTrajectory.h"

RealSystemTrajectory::RealSystemTrajectory(SimDPreference &SimPref) :Trajectory3Dof(SimPref)
{

	airframe = new Airframe;
	guidance = new Guidance(SimPref);
	autopilot = new Autopilot;

	imu			= new IMU(SimPref);
	navigation  = new Navigation(SimPref);
	actuator	= new Actuator(SimPref);
	gps			= new GPS(SimPref);
}

RealSystemTrajectory::~RealSystemTrajectory()
{
}

void RealSystemTrajectory::initTrajectory(Float64 &FlightTime, 
										  AerodynamicStruct & AeroData, 
										  AirframeStruct & AirframeData, 
										  ThrustStruct & ThrustData, 
										  AircraftStruct & AircraftData,
									      GuidanceStruct & GuidanceData, 
										  NavigationStruct & NavData, 
										  ActuatorStruct & ActuatorData, 
									      IMUStruct & IMUData)
{

	initTrajectory3DoF(FlightTime,
					   AeroData,
					   AirframeData,
					   ThrustData,
					   AircraftData);


	autopilot->initAutopilot();

	guidance->initGuidance(FlightTime,
						   GuidanceData, 
						   AircraftData);

	gps->initGPS();

	imu->initIMU(IMUData);

	navigation->initNavigation(FlightTime, 
							   NavData, 
							   IMUData);

	actuator->initActuator(FlightTime,
							AirframeData,
							ActuatorData);
}

void RealSystemTrajectory::updateTrajectory(Float64 FlightTime, 
											AtmosphereStruct & AtmoData, 
											AerodynamicStruct & AeroData, 
											AirframeStruct & AirframeData, 
											ThrustStruct & ThrustData, 
											GuidanceStruct & GuidanceData, 
											NavigationStruct & NavData, 
											ActuatorStruct & ActuatorData, 
											IMUStruct & IMUData)
{

	gps->updateGPS(FlightTime,
					NavData,
					AirframeData);

	navigation->updateNavigation(FlightTime,
								 NavData,
								 AirframeData, 
								 IMUData);


	updateTrajectory3DoF(FlightTime,
						 AtmoData,
						 AeroData,
						 AirframeData,
						 ThrustData,
						 ActuatorData,
						 IMUData,
						 NavData);

	airframe->updateRotatory(AeroData,
							 ThrustData,
							 AirframeData);

	imu->updateIMU(FlightTime,
				   AirframeData,
				   IMUData);

	guidance->updateGuidance(FlightTime,
							 AeroData,
							 ThrustData,
							 AirframeData,
							 GuidanceData);

	autopilot->updateAutopilot(FlightTime,
							   AirframeData,
							   AeroData,
							   GuidanceData,
							   ActuatorData,
							   IMUData,
							   NavData);

	actuator->updateActuator(FlightTime,
							AirframeData,
							ActuatorData);



	logRealsystemTrajectory();

}

void RealSystemTrajectory::logRealsystemTrajectory()
{
	guidance->logGuidanceData();
	navigation->logNavigationData();

	log3DofData();
}

