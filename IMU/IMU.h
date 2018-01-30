#pragma once
#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseIMU.h"
#include"flawlessIMU.h"

class IMU
{
public:
	IMU();

	~IMU();

	void selectIMU(int Type);

	void initIMU();


	void updateIMU(Float64 FlightTime, 
				   AirframeStruct & AirframeData, IMUStruct &IMUData);

private:
	BaseIMU * imu;
};