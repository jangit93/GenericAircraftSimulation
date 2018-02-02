#pragma once


#include"BaseGPS.h"

class flawlessGPS : public BaseGPS
{
public:

	flawlessGPS();

	~flawlessGPS();

	void initGPS();

	void updateGPS(Float64 FlightTime, NavigationStruct &NavData);

private:

};