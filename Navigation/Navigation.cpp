#include "Navigation.h"
#include<iostream>
Navigation::Navigation(SimDPreference &SimPref)
{

	selectNavigation(SimPref.NavMode);
}

Navigation::~Navigation()
{
}

void Navigation::selectNavigation(int Type)
{
	switch (Type)
	{
	case 1:
		std::cout << "Navigation:\t" << "flawless Navigation" << std::endl;
		navigation = new flawlessNavigation;
		break;
	}
}

void Navigation::initNavigation(Float64 & FlightTime,
								NavigationStruct & NavData,
								IMUStruct &IMUData)
{
	navigation->initNavigation(FlightTime,
							   NavData,
							   IMUData);
}

void Navigation::updateNavigation(Float64 FlightTime,
								  NavigationStruct & NavData,	
								  AirframeStruct &AirframeData, 
								  IMUStruct& IMUData)
{
	navigation->updateNavigation(FlightTime,
								 NavData,
								 AirframeData,
								 IMUData);
}

void Navigation::logNavigationData()
{
	navigation->logNavigationData();
}
