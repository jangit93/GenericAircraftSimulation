#include "Navigation.h"

Navigation::Navigation()
{
	int type = 1;

	selectNavigation(type);
}

Navigation::~Navigation()
{
}

void Navigation::selectNavigation(int Type)
{
	switch (Type)
	{
	case 1:
		navigation = new BaseNavigation;
		break;
	case 2:
		break;
	}
}

void Navigation::initNavigation()
{
	navigation->initNavigation();
}

void Navigation::updateNavigation(Float64 FlightTime, NavigationStruct & NavData, GuidanceStruct & GuidanceData)
{
	navigation->updateNavigation(FlightTime, NavData, GuidanceData);
}
