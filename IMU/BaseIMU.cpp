#include "BaseIMU.h"

BaseIMU::BaseIMU()
{
}

BaseIMU::~BaseIMU()
{
}

void BaseIMU::initIMU()
{
	this->initializeIMU();
}

void BaseIMU::initializeIMU()
{
}

void BaseIMU::updateIMU(Float64 Flighttime, 
						AirframeStruct & AirframeData,  IMUStruct &IMUData)
{
	this->calcIMU(Flighttime, AirframeData,IMUData);
}

void BaseIMU::calcIMU(Float64 Flighttime,	
					  AirframeStruct & AirframeData, IMUStruct &IMUData)
{
}
