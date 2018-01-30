#pragma once


#include"BaseGPS.h"

class flawlessGPS : public BaseGPS
{
public:

	flawlessGPS();

	~flawlessGPS();

	void initializeGPS();

	void calcGPS(Float64 FlightTime, NavigationStruct &NavData);

private:

};