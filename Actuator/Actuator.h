#pragma once
#include"../DataCloud/DataCloud.h"
#include"BaseActuator.h"
#include"flawlessActuator.h"
#include<iostream>

class Actuator
{
public:
	Actuator(SimDPreference &SimPref);

	~Actuator();

	void initActuator(Float64 &FlightTime,
					  AirframeStruct & AirframeData, 
					  ActuatorStruct &ActuatorData);

	void selectActuatorType(int type);

	void updateActuator(Float64 &FlightTime,
						AirframeStruct & AirframeData,
						ActuatorStruct &ActuatorData);

	void logActuator();

private:
	BaseActuator * actuator;
};