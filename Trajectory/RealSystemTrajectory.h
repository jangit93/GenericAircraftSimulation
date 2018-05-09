#pragma once
#include"DataCloud.h"
#include"Trajectory6DoF.h"
#include"Autopilot.h"
#include"Guidance.h"
#include"Airframe.h"
#include"Navigation.h"
#include"IMU.h"
#include"Actuator.h"

class RealSystemTrajectory : public Trajectory6Dof
{
public:
	RealSystemTrajectory(SimDPreference &SimPref);

	~RealSystemTrajectory();

	void initTrajectory(Float64 FlightTime,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData,
						AircraftStruct &AircraftData,
						GuidanceStruct &GuidanceData,
						NavigationStruct &NavData,
						ActuatorStruct &ActuatorData,
						IMUStruct &IMUData);

	void updateTrajectory(Float64 FlightTime,
						  AtmosphereStruct & AtmoData,
						  AerodynamicStruct & AeroData,
						  AirframeStruct & AirframeData,
						  ThrustStruct & ThrustData,
						  GuidanceStruct & GuidanceData,
						  NavigationStruct &NavData,
						  ActuatorStruct &ActuatorData,
						  IMUStruct &IMUData);


	void logRealsystemTrajectory();
private:
	Autopilot * autopilot;
	Guidance  *guidance;
	Airframe     *airframe;
	IMU *imu;
	Navigation *navigation;
	Actuator *actuator;
};