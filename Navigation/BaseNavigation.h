#pragma once
#pragma once


#include"../DataCloud/DataCloud.h"

class BaseNavigation
{
public:
	BaseNavigation();

	~BaseNavigation();

	void initNavigation();

	virtual void updateNavigation(Float64 Flighttime, 
						  NavigationStruct &NavData,
						  GuidanceStruct &GuidanecData);




private:

};