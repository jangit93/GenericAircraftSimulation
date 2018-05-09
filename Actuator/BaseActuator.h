#pragma once
#include"../DataCloud/DataCloud.h"

class BaseActuator
{
public:	
	BaseActuator();

	~BaseActuator();

	virtual void initActuator(Float64 & FlightTime,
							  AirframeStruct & AirframeData,
							  ActuatorStruct & ActuatorData);

	virtual void updateActuator(Float64 & FlightTime,
								AirframeStruct & AirframeData,
								ActuatorStruct & ActuatorData);

	virtual void LogActuatorData();

private:

	

};