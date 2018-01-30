#pragma once


#include"../DataCloud/DataCloud.h"

class BaseGPS
{
public:
	BaseGPS();

	~BaseGPS();

	void initGPS();

	virtual void initializeGPS();

	void updateGPS(Float64 Flighttime, NavigationStruct &NavData);

	virtual void calcGPS(Float64 Flighttime, NavigationStruct &NavData);


private:

};