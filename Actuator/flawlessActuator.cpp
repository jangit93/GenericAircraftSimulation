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

	initLogActuatorData(FlightTime, 
						ActuatorData);
}

void flawlessActuator::updateActuator(Float64 FlightTime,
									  AirframeStruct & AirframeData,
									  ActuatorStruct & ActuatorData)
{
	ActuatorData.Eta	= ActuatorData.Eta;
	ActuatorData.Xi		= ActuatorData.Xi;
	ActuatorData.Zeta	= ActuatorData.Zeta;
}

void flawlessActuator::initLogActuatorData(Float64 & FlightTime,
										   ActuatorStruct & ActuatorData)
{
	
	logActuatorData->add("Eta", ActuatorData.Eta);
	logActuatorData->add("Xi", ActuatorData.Xi);
	logActuatorData->add("Zeta", ActuatorData.Zeta);
	logActuatorData->add("Delta", ActuatorData.Delta);

	logActuatorData->printHeader();
}

void flawlessActuator::LogActuatorData()
{
	logActuatorData->print();
}
