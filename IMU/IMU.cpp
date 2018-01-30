#include "IMU.h"

IMU::IMU()
{
	int Type = 2;
	selectIMU(Type);
}

IMU::~IMU()
{
}

void IMU::selectIMU(int Type)
{
	switch (Type)
	{
	case 1:
		imu = new BaseIMU;
		break;
	case 2:
		imu = new flawlessIMU;
	}
}

void IMU::initIMU()
{
	imu->initIMU();
}

void IMU::updateIMU(Float64 FlightTime, AirframeStruct & AirframeData, IMUStruct &IMUData)
{
	imu->updateIMU(FlightTime, AirframeData, IMUData);
}
