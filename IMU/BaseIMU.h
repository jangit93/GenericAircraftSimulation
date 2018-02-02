#pragma once


#include"../DataCloud/DataCloud.h"


class BaseIMU
{
public:
	BaseIMU();

	~BaseIMU();

    virtual void initIMU();

	virtual void updateIMU(Float64 Flighttime, AirframeStruct & AirframeData,IMUStruct &IMUData);



private:
};