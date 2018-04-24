#pragma once
#include<Eigen/dense>
#include<iostream>
#include"DataCloud.h"
#include"IndependetDataTypes.h"

class BaseGuidance 
{
public:
	BaseGuidance();

	~BaseGuidance();

	virtual void initGuidance(Float64 &FlightTime, GuidanceStruct &GuidanceData,AircraftStruct &AircraftData);

	virtual void updateGuidance(Float64 FlightTime,
						AerodynamicStruct &AeroData,
						ThrustStruct &ThrustData,
						AirframeStruct &AirframeData,
						GuidanceStruct &GuidanceData);

	virtual void initLogGuidance(Float64 FlightTime, GuidanceStruct &GuidanceData);

	virtual void logGuidanceData();


private:

};