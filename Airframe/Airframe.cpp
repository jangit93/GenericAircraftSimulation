#include "Airframe.h"

Airframe::Airframe()
{
	readIn = new readInData;
	LogAirframeData = new DataLogger("AirframeData.txt", 25, " ");
}

Airframe::~Airframe()
{
}

void Airframe::initAirframe(Float64 &FlightTime,
							AircraftStruct & AircraftData,
							AirframeStruct & AirframeData)
{
	/// 1) read in geometric aircraft data (wingspan,...)
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
	AirframeData.intertiaTensor(0, 2) = -(readIn->readInParameter("I_zx", "Aircraft.txt"));

	AirframeData.intertiaTensor(1, 0) = 0;
	AirframeData.intertiaTensor(1, 1) = readIn->readInParameter("I_Y", "Aircraft.txt");
	AirframeData.intertiaTensor(1, 2) = 0;

	AirframeData.intertiaTensor(2, 0) = -(readIn->readInParameter("I_zx", "Aircraft.txt"));
	AirframeData.intertiaTensor(2, 1) = 0;
	AirframeData.intertiaTensor(2, 2) = readIn->readInParameter("I_Z", "Aircraft.txt");

	/// 3) initialize airframe data
	AirframeData.accRotBody.setZero();
	AirframeData.accRotNED.setZero();
	AirframeData.accTransBody.setZero();
	AirframeData.accTransNED.setZero();
	AirframeData.EulerAngles.setZero();
	AirframeData.Eulerdot.setZero();
	AirframeData.matBodyToNED.setZero();
	AirframeData.matNEDToBody.setZero();
	AirframeData.matNEDToTraj.setZero();
	AirframeData.posNED.setZero();
	AirframeData.velBody.setZero();
	AirframeData.velNED.setZero();
	AirframeData.rotRatesBody.setZero();

	AirframeData.Xi		= 0.0;
	AirframeData.Eta	= 0.0;
	AirframeData.Zeta	= 0.0;

	initLogAirframeData(FlightTime, 
						AirframeData);
	
}

void Airframe::updateTranslational(AerodynamicStruct &AeroData, 
								   ThrustStruct &ThrustData,
								   AirframeStruct &AirframeData)
{
	/// 1) get data from structs
	phi		= AirframeData.EulerAngles(0);
	theta	= AirframeData.EulerAngles(1);

	AoA = AeroData.Alpha *PI / 180;
	AoS = AeroData.Beta *PI / 180;

	/// 2) calculate translational accelerations
	TotalForce = AeroData.AeroForces + ThrustData.ThrustForce;

	Vec_fg << -sin(theta),
			sin(phi)*cos(theta),
			cos(phi)*cos(theta);

	AirframeData.accTransBody = (TotalForce / mass) + Vec_fg  * GRAVITATIONAL_CONSTANT;
	AirframeData.accTransNED  = AirframeData.matBodyToNED*AirframeData.accTransBody;
}

void Airframe::updateRotatory(AerodynamicStruct &AeroData, 
							  ThrustStruct &ThrustData,
							  AirframeStruct &AirframeData)
{
	/// 1) get data from structs
	phi   = AirframeData.EulerAngles(0);
	theta = AirframeData.EulerAngles(1);

	p = AirframeData.rotRatesBody(0);
	q = AirframeData.rotRatesBody(1);
	r = AirframeData.rotRatesBody(2);

	/// 2) calculate rotatory accelerations
	TotalMoment = AeroData.AeroMoments + ThrustData.ThrustMoments;

	Vec_rotTensor << q*r*(AirframeData.intertiaTensor(2, 2) - AirframeData.intertiaTensor(1, 1)) - p * q*AirframeData.intertiaTensor(0,2),
					 r*p*(AirframeData.intertiaTensor(0, 0) - AirframeData.intertiaTensor(2, 2)) + (p*p - r * r)*AirframeData.intertiaTensor(0, 2),
					 p*q*(AirframeData.intertiaTensor(1, 1) - AirframeData.intertiaTensor(0, 0)) + q * r*AirframeData.intertiaTensor(0, 2);


	/// 3)  calculate derivation of euler angles
	AirframeData.accRotBody = AirframeData.intertiaTensor.inverse()*(TotalMoment - Vec_rotTensor);

	Eulerdot << 1, sin(phi) * tan(theta), cos(phi) * tan(theta),
				0, cos(phi), -sin(phi),
				0, (sin(phi) / cos(theta)), (cos(phi) / cos(theta));

	AirframeData.Eulerdot = Eulerdot *AirframeData.rotRatesBody;

}

void Airframe::initLogAirframeData(Float64 & FlightTime, AirframeStruct & AirframeData)
{
	LogAirframeData->add("FlightTime [s]", FlightTime);
	LogAirframeData->add("Gamma", AirframeData.Gamma);
	LogAirframeData->add("Chi", AirframeData.Chi);

	LogAirframeData->printHeader();
}

void Airframe::logAirframeData()
{
	LogAirframeData->print();
}
