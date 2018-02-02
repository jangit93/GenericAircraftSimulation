#pragma once
#include<Eigen/dense>
#include"../GPS/GPS.h"
#include"../Guidance/Guidance.h"
#include"../Tools/IndependetDataTypes.h"
#include"../Tools/ODEsolver.cpp"
#include"BaseNavigation.h"
#include"flawlessNavigation.h"

class Navigation
{
public:
	Navigation();

	~Navigation();

	void selectNavigation(int Type);

	void initNavigation();


	void updateNavigation(Float64 FlightTime,
						NavigationStruct & NavData,
						GuidanceStruct &GuidanceData);

private:
	BaseNavigation * navigation;
};