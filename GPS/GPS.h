#pragma once
#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseGPS.h"
#include"flawlessGPS.h"

class GPS
{
public:
	GPS();

	~GPS();

	void selectGPS(int Type);

	void initGPS();


	void updateGPS(Float64 FlightTime,
					NavigationStruct & NavData);

private:
	BaseGPS * gps;
};