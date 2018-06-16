#include "flawlessNavigation.h"

flawlessNavigation::flawlessNavigation()
{
	Trafo = new Transformation;
	lognavigationData = new DataLogger("NavigationData.txt", 25, " ");
}

flawlessNavigation::~flawlessNavigation()
{
}

void flawlessNavigation::initNavigation(Float64 & FlightTime,
										NavigationStruct & NavData,
										IMUStruct &IMUData)
{
	NavData.absVel = 0.0;
	NavData.posNED.setZero();
	NavData.velNED.setZero();

	initlogNavigationData(FlightTime,
						  NavData, 
						  IMUData);
}

void flawlessNavigation::updateNavigation(Float64 Flighttime, 
										  NavigationStruct & NavData, 
										  AirframeStruct &AirframeData,
										  IMUStruct &IMUData)
{
	NavData.velNED = EulerIntegration(NavData.velNED, IMUData.accTransNED, NavData.dt);
	NavData.posNED = EulerIntegration(NavData.posNED, NavData.velNED, NavData.dt);

	NavData.absVel = NavData.velNED.norm();

	NavData.EulerAngles = EulerIntegration(NavData.EulerAngles, AirframeData.Eulerdot, NavData.dt);
	AirframeData.EulerAngles = NavData.EulerAngles;
	AirframeData.Gamma = atan2(-NavData.velNED(2), sqrt(NavData.velNED(0)*NavData.velNED(0) + NavData.velNED(1)*NavData.velNED(1)));
	AirframeData.Chi = atan2(NavData.velNED(1), NavData.velNED(0));

	AirframeData.matNEDToBody = Trafo->MatNedToBody(NavData.EulerAngles(0), NavData.EulerAngles(1), NavData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo->MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);
}

void flawlessNavigation::initlogNavigationData(Float64 & FlightTime, 
											   NavigationStruct & NavData,
											   IMUStruct & IMUData)
{
	

	lognavigationData->add("FlightTime [s]", FlightTime);
	lognavigationData->add("Velocity", NavData.absVel);
	lognavigationData->add("x_NED", NavData.posNED(0));
	lognavigationData->add("y_NED", NavData.posNED(1));
	lognavigationData->add("z_NED", NavData.posNED(2));
	lognavigationData->add("phi",   NavData.EulerAngles(0));
	lognavigationData->add("theta", NavData.EulerAngles(1));
	lognavigationData->add("psi",   NavData.EulerAngles(2));

	lognavigationData->printHeader();

	
}

void flawlessNavigation::logNavigationData()
{
	lognavigationData->print();
}
