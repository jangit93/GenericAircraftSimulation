#pragma once
#include"../DataCloud/DataCloud.h"
#include"MatFileReader.h"
#include"Trajectory.h"
#include"Atmosphere.h"

class Aircraft
{
public:
	Aircraft(SimDPreference &SimPref);

	~Aircraft();

	void initAircraft();

	void simulateAircraft();


	

private:
	
	Trajectory * trajectory;
	Atmopshere *Atmo;
	AutopilotStruct * TrimPoints;
	Float64 FlightTime;
	AirframeStruct AirframeData;
	AtmosphereStruct	AtmoData;
	AerodynamicStruct	AeroData;
	ThrustStruct		ThrustData;
	AircraftStruct		AircraftData;
	GuidanceStruct		GuidanceData;
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;
	IMUStruct IMUData;
	int Fields;

};