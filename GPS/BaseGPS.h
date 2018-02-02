#pragma once


#include"../DataCloud/DataCloud.h"

class BaseGPS
{
public:
	BaseGPS();

	~BaseGPS();

	virtual void initGPS();

	virtual void updateGPS(Float64 Flighttime, NavigationStruct &NavData);



private:

};