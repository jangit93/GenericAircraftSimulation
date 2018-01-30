#include "Guidance.h"

Guidance::Guidance()
{
	int type = 2;

	selectGuidance(type);
}

Guidance::~Guidance()
{
}

void Guidance::selectGuidance(int Type)
{
	switch (Type)
	{
	case 1:
		std::cout << "Guidance\t" << "Base Guidance" << std::endl;
		guidance = new BaseGuidance;
		break;
	case 2:
		std::cout << "Guidance\t" << "acceleration Table Guidance" << std::endl;
		guidance = new accTable;
		break;

	}
}

void Guidance::initGuidance()
{
	guidance->initGuidance();
}

void Guidance::updateGuidance(Float64 FlightTime, 
							  AerodynamicStruct & AeroData,
							  ThrustStruct & ThrustData, 
							  AircraftStruct & AircraftData, 
							  AirframeStruct & AirframeData, 
							  AtmosphereStruct & AtmosphereData, 
						      GuidanceStruct &GuidanceData)
{
	guidance->updateGuidance(FlightTime,
							 AeroData,
							 ThrustData,
							 AircraftData,
							 AirframeData,
							 AtmosphereData,
							 GuidanceData);
}
