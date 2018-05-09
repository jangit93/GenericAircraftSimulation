#include "flawlessActuator.h"

flawlessActuator::flawlessActuator()
{
	logActuatorData = new DataLogger("ActuatorData.txt", 25, " ");
}

flawlessActuator::~flawlessActuator()
{
}

void flawlessActuator::initActuator(Float64 & FlightTime,
									AirframeStruct & AirframeData,
									ActuatorStruct & ActuatorData)
{
	ActuatorData.realEta = 0.0;
	ActuatorData.realXi = 0.0;
	ActuatorData.realZeta = 0.0;

	initLogActuatorData(FlightTime, ActuatorData);
}

void flawlessActuator::updateActuator(Float64 & FlightTime,
									  AirframeStruct & AirframeData,
									  ActuatorStruct & ActuatorData)
{
	ActuatorData.realEta	= AirframeData.Eta;
	ActuatorData.realXi		= AirframeData.Xi;
	ActuatorData.realZeta	= AirframeData.Zeta;
}

void flawlessActuator::initLogActuatorData(Float64 & FlightTime,
										   ActuatorStruct & ActuatorData)
{
	logActuatorData->add("FlightTime", FlightTime);
	logActuatorData->add("realEta", ActuatorData.realEta);
	logActuatorData->add("realXi", ActuatorData.realXi);
	logActuatorData->add("realZeta", ActuatorData.realZeta);

	logActuatorData->printHeader();
}

void flawlessActuator::LogActuatorData()
{
	logActuatorData->print();
}
