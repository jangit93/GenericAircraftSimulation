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
	AirframeData.velNED = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, NavData.dt);
	AirframeData.posNED = EulerIntegration(AirframeData.posNED, AirframeData.velNED, NavData.dt);

	
	AirframeData.EulerAngles = EulerIntegration(AirframeData.EulerAngles, AirframeData.Eulerdot, NavData.dt);

	AirframeData.Gamma = atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(1)*AirframeData.velNED(1)));


	AirframeData.Chi = atan2(AirframeData.velNED(1), AirframeData.velNED(0));

	AirframeData.matNEDToBody = Trafo->MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo->MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);
}
