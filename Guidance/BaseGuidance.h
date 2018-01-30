#pragma once
#include<Eigen/dense>
#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"

class BaseGuidance 
{
public:
	BaseGuidance();

	~BaseGuidance();

	void initGuidance();

	void updateGuidance(Float64 FlightTime,
						AerodynamicStruct &AeroData,
						ThrustStruct &ThrustData,
						AircraftStruct &AircraftData,
						AirframeStruct &AirframeData,
						AtmosphereStruct & AtmosphereData,
						GuidanceStruct &GuidanceData);

	virtual void initializeGuidance();

	virtual void calcGuidance(Float64 FlightTime,
							  AerodynamicStruct &AeroData,
							  ThrustStruct &ThrustData,
							  AircraftStruct &AircraftData,
							  AirframeStruct &AirframeData,
							  AtmosphereStruct & AtmosphereData,
							  GuidanceStruct &GuidanceData);

private:

};