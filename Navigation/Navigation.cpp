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
		std::cout << "Navigation:\t" << "Base Navigation" << std::endl;
		navigation = new BaseNavigation;
		break;
	}
}

void Navigation::initNavigation()
{
	navigation->initNavigation();
}

void Navigation::updateNavigation(Float64 FlightTime, NavigationStruct & NavData, AirframeStruct &AirframeData)
{
	navigation->updateNavigation(FlightTime, NavData, AirframeData);
}
