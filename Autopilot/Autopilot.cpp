#include "Autopilot.h"

Autopilot::Autopilot()
{
	controller = new StateController;
}

Autopilot::~Autopilot()
{
}


void Autopilot::initAutopilot()
{
	controller->initStateController();
	
}

void Autopilot::updateAutopilot(Float64 FlightTime,
								AirframeStruct &AirframeData,
								AerodynamicStruct &AeroData,
								GuidanceStruct &GuidanceData, 
								ActuatorStruct &ActuatorData, 
								IMUStruct &IMUData, 
								NavigationStruct &NavData)
{
	controller->updateStateController(FlightTime,
									  AirframeData,
									  AeroData,
									  GuidanceData,
									  ActuatorData,
									  IMUData,
									  NavData);
}
