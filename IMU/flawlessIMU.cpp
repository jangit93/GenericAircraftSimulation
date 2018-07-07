#include "flawlessIMU.h"

flawlessIMU::flawlessIMU()
{
	logimuData = new DataLogger("IMUData.txt", 25, " ");
}

flawlessIMU::~flawlessIMU()
{
}

void flawlessIMU::initIMU(IMUStruct & IMUData)
{
	IMUData.accRotBody.setZero();
	IMUData.rotRatesBody.setZero();
	IMUData.accTransNED.setZero();
	IMUData.realTRotAcc.setZero();

	initlogIMUData(IMUData);
}

void flawlessIMU::updateIMU(Float64 FlightTime, 
							AirframeStruct & AirframeData, 
							IMUStruct & IMUData)
{
	IMUData.realTRotAcc = AirframeData.accRotBody;
	IMUData.accTransNED = AirframeData.accTransNED;
	
	IMUData.rotRatesBody = EulerIntegration(IMUData.rotRatesBody, IMUData.realTRotAcc, IMUData.dt);
	AirframeData.rotRatesBody = IMUData.rotRatesBody;
}

void flawlessIMU::initlogIMUData(IMUStruct & IMUData)
{
	logimuData->add("roll-rate", IMUData.rotRatesBody(0));
	logimuData->add("pitch-rate", IMUData.rotRatesBody(1));
	logimuData->add("yaw-rate", IMUData.rotRatesBody(2));
	logimuData->add("acc_x_NED", IMUData.accTransNED(0));
	logimuData->add("acc_y_NED", IMUData.accTransNED(1));
	logimuData->add("acc_z_NED", IMUData.accTransNED(2));
	
	logimuData->printHeader();
}

void flawlessIMU::logIMUData()
{
	logimuData->print();
}
