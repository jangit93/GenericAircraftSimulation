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

	virtual void initGuidance();

	virtual void updateGuidance(Float64 FlightTime,
						AerodynamicStruct &AeroData,
						ThrustStruct &ThrustData,
						AircraftStruct &AircraftData,
						AirframeStruct &AirframeData,
						AtmosphereStruct & AtmosphereData,
						GuidanceStruct &GuidanceData);


private:

};