#include "Actuator.h"

Actuator::Actuator(SimDPreference &SimPref)
{
	selectActuatorType(SimPref.ActuatorMode);
}

Actuator::~Actuator()
{
}

void Actuator::initActuator(Float64 & FlightTime,
							AirframeStruct & AirframeData, 
							ActuatorStruct & ActuatorData)
{
	actuator->initActuator(FlightTime,
						   AirframeData,
						   ActuatorData);
}

void Actuator::selectActuatorType(int type)
{
	switch (type)
	{
	case 1:
		std::cout << "Actuator:\t" << "flawless Actuator" << std::endl;
		actuator = new flawlessActuator();
		break;
	}
}

void Actuator::updateActuator(Float64  FlightTime,
							  AirframeStruct & AirframeData, 
							  ActuatorStruct & ActuatorData)
{
	actuator->updateActuator(FlightTime,
							AirframeData,
							ActuatorData);
}


void Actuator::logActuator()
{
	actuator->LogActuatorData();
}
