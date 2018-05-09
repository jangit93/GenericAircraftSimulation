#include "IMU.h"

IMU::IMU(SimDPreference &SimPref)
{
	selectIMU(SimPref.IMUMode);
}

IMU::~IMU()
{
}

void IMU::selectIMU(int Type)
{
	switch (Type)
	{
	case 1:
		std::cout << "IMU:\t\t" << "flawless IMU" << std::endl;
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
