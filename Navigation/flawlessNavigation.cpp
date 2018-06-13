#include "flawlessNavigation.h"

flawlessNavigation::flawlessNavigation()
{
	Trafo = new Transformation;
}

flawlessNavigation::~flawlessNavigation()
{
}

void flawlessNavigation::initNavigation(NavigationStruct & NavData)
{

}

void flawlessNavigation::updateNavigation(Float64 Flighttime, 
										  NavigationStruct & NavData, 
										  AirframeStruct &AirframeData)
{
	NavData.velNED = EulerIntegration(NavData.velNED, AirframeData.accTransNED, NavData.dt);
	NavData.posNED = EulerIntegration(NavData.posNED, NavData.velNED, NavData.dt);
	AirframeData.posNED = NavData.posNED;
	AirframeData.velNED = NavData.velNED;

	NavData.EulerAngles = EulerIntegration(NavData.EulerAngles, AirframeData.Eulerdot, NavData.dt);
	AirframeData.EulerAngles = NavData.EulerAngles;
	AirframeData.Gamma = atan2(-NavData.velNED(2), sqrt(NavData.velNED(0)*NavData.velNED(0) + NavData.velNED(1)*NavData.velNED(1)));
	AirframeData.Chi = atan2(NavData.velNED(1), NavData.velNED(0));

	AirframeData.matNEDToBody = Trafo->MatNedToBody(NavData.EulerAngles(0), NavData.EulerAngles(1), NavData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo->MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);
}
