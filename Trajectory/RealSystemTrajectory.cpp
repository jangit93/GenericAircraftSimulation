#include "RealSystemTrajectory.h"

RealSystemTrajectory::RealSystemTrajectory(SimDPreference &SimPref) :Trajectory6Dof(SimPref)
{
	airframe = new Airframe;
	imu = new IMU(SimPref);
	navigation = new Navigation(SimPref);
	actuator = new Actuator(SimPref);
}

RealSystemTrajectory::~RealSystemTrajectory()
{
}

void RealSystemTrajectory::initTrajectory(Float64 FlightTime, 
										  AerodynamicStruct & AeroData, 
										  AirframeStruct & AirframeData, 
										  ThrustStruct & ThrustData, 
										  AircraftStruct & AircraftData,
									      GuidanceStruct & GuidanceData, 
										  NavigationStruct & NavData, 
										  ActuatorStruct & ActuatorData, 
									      IMUStruct & IMUData)
{
	initTrajectory6Dof(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData,
						GuidanceData,
						NavData);

	imu->initIMU();

	navigation->initNavigation();

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

	imu->updateIMU(FlightTime,
				   AirframeData,
				   IMUData);

	navigation->updateNavigation(FlightTime,
								NavData,
								AirframeData);

	updateTrajectory6Dof(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						GuidanceData,
						NavData);


	actuator->updateActuator(FlightTime,
							AirframeData,
							ActuatorData);

	logRealsystemTrajectory();

}

void RealSystemTrajectory::logRealsystemTrajectory()
{
	log6DofData();
}

