#pragma once


#include"../DataCloud/DataCloud.h"


class BaseIMU
{
public:
	BaseIMU();

	~BaseIMU();

	void initIMU();

	virtual void initializeIMU();

	void updateIMU(Float64 Flighttime, AirframeStruct & AirframeData,IMUStruct &IMUData);

	virtual void calcIMU(Float64 Flighttime, AirframeStruct & AirframeData, IMUStruct &IMUData);

	


private:
};