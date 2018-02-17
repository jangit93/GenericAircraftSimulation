#pragma once
#include<Eigen/dense>
#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseGuidance.h"
#include"accTable.h"

class Guidance
{
public:

	Guidance();

	~Guidance();

	void selectGuidance(int Type);

	void initGuidance();

	void updateGuidance(Float64 FlightTime, 
						AerodynamicStruct & AeroData, 
						ThrustStruct & ThrustData,
						AirframeStruct & AirframeData, 
						GuidanceStruct & GuidanceData);


private:
	BaseGuidance * guidance;
};