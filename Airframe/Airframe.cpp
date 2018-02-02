#include "Airframe.h"

Airframe::Airframe()
{
	readIn = new readInData;
}

Airframe::~Airframe()
{
}

void Airframe::initAirframe(AircraftStruct & AircraftData,
							AirframeStruct & AirframeData)
{
	mass = readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.mass 		= readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.wingarea 	= readIn->readInParameter("wing_area", "Aircraft.txt");
	AircraftData.wingspan 	= readIn->readInParameter("wing_span", "Aircraft.txt");
	AircraftData.MAC 		= readIn->readInParameter("MAC", "Aircraft.txt");
	AircraftData.X_CG 		= readIn->readInParameter("X_CG", "Aircraft.txt");
	AircraftData.Y_CG		= readIn->readInParameter("Y_CG", "Aircraft.txt");
	AircraftData.Z_CG		= readIn->readInParameter("Z_CG", "Aircraft.txt");


	AirframeData.intertiaTensor(0, 0) = readIn->readInParameter("I_X", "Aircraft.txt");
	AirframeData.intertiaTensor(0, 1) = 0;
	AirframeData.intertiaTensor(0, 2) = readIn->readInParameter("I_zx", "Aircraft.txt");

	AirframeData.intertiaTensor(1, 0) = 0;
	AirframeData.intertiaTensor(1, 1) = readIn->readInParameter("I_Y", "Aircraft.txt");
	AirframeData.intertiaTensor(1, 2) = 0;

	AirframeData.intertiaTensor(2, 0) = readIn->readInParameter("I_zx", "Aircraft.txt");
	AirframeData.intertiaTensor(2, 1) = 0;
	AirframeData.intertiaTensor(2, 2) = readIn->readInParameter("I_Z", "Aircraft.txt");
}

void Airframe::updateTranslational(AerodynamicStruct & AeroData, 
								   ThrustStruct & ThrustData,
									AirframeStruct & AirframeData)
{
	phi		= AirframeData.EulerAngles(0);
	theta	= AirframeData.EulerAngles(1);

	AoA = AeroData.AoA *PI / 180;
	AoS = AeroData.AoS *PI / 180;

	TotalForce = AeroData.AeroForces + ThrustData.ThrustForce;

	Vec_fg << -sin(theta),
			sin(phi)*cos(theta);
			cos(phi)*cos(theta);

	AirframeData.accTransBody = (TotalForce / mass) + Vec_fg  * GRAVITATIONAL_CONSTANT;
}

void Airframe::updateRotational(AerodynamicStruct & AeroData, 
								ThrustStruct & ThrustData,
								AirframeStruct &AirframeData)
{
	p = AirframeData.rotRatesBody(0);
	q = AirframeData.rotRatesBody(1);
	r = AirframeData.rotRatesBody(2);

	rotRates << p, q, r;
	TotalMoment = AeroData.AeroMoments + ThrustData.ThrustMoments;

	Vec_rotTensor << q*r*(AirframeData.intertiaTensor(2, 2) - AirframeData.intertiaTensor(1, 1)) - p*q*AirframeData.intertiaTensor(0, 2),
		r*p*(AirframeData.intertiaTensor(0, 0) - AirframeData.intertiaTensor(2, 2)) + (p*p - r*r)*AirframeData.intertiaTensor(0, 2),
		p*q*(AirframeData.intertiaTensor(1, 1) - AirframeData.intertiaTensor(0, 0)) + q*r*AirframeData.intertiaTensor(0, 2);

	AirframeData.accRotBody = AirframeData.intertiaTensor.inverse()*(TotalMoment - Vec_rotTensor);

	Eulerdot << 1, sin(phi) * tan(theta), cos(phi) * tan(theta),
				0, cos(phi), -sin(phi),
				0, sin(phi) / cos(theta), cos(phi) / cos(theta);

	AirframeData.Eulerdot = Eulerdot *rotRates;

}
