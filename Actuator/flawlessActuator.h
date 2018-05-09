#pragma once

#include"BaseActuator.h"
#include"../Tools/DataLogger.h"

class flawlessActuator : public BaseActuator
{
public:
	flawlessActuator();

	~flawlessActuator();

	virtual void initActuator(Float64 & FlightTime,
							  AirframeStruct & AirframeData,
							  ActuatorStruct & ActuatorData);

	virtual void updateActuator(Float64 & FlightTime,
							    AirframeStruct & AirframeData,
								ActuatorStruct & ActuatorData);

	void initLogActuatorData(Float64 & FlightTime,
							 ActuatorStruct & ActuatorData);

	void LogActuatorData();

private:
	DataLogger * logActuatorData;



};