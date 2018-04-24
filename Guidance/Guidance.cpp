#include "Guidance.h"

Guidance::Guidance(SimDPreference &SimPref)
{
	selectGuidance(SimPref.GuidanceMode);

}

Guidance::~Guidance()
{
}

void Guidance::selectGuidance(int Type)
{
	switch (Type)
	{
	case 1:
		std::cout << "Guidance:\t" << "Base Guidance" << std::endl;
		guidance = new BaseGuidance;
		break;
	case 2:
		std::cout << "Guidance:\t" << "acceleration Table Guidance" << std::endl;
		guidance = new accTable;
		break;

	}
}

void Guidance::initGuidance(Float64 &FlightTime, GuidanceStruct &GuidanceData, AircraftStruct &AircraftData)
{
	guidance->initGuidance(FlightTime,GuidanceData,AircraftData);
	
}

void Guidance::updateGuidance(Float64 FlightTime, 
							  AerodynamicStruct & AeroData,
							  ThrustStruct & ThrustData,  
							  AirframeStruct & AirframeData,
						      GuidanceStruct &GuidanceData)
{
	guidance->updateGuidance(FlightTime,
							 AeroData,
							 ThrustData,
							 AirframeData,
							 GuidanceData);
}

void Guidance::logGuidanceData()
{
	guidance->logGuidanceData();
}
