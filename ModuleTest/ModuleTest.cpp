#include"Atmosphere.h"
#include"Autopilot.h"
#include"StateController.h"
#include"FindNeighbor.h"
#include"Aerodynamic.h"
#include"DataLogger.h"
#include"readInData.h"
#include"MatFileReader.h"
#include"Guidance.h"
#include"Transformation.h"
#include"GPS.h"
#include"IMU.h"
#include"Navigation.h"
#include<iostream>
#include<omp.h>

void AtmosphereTest()
{

	Atmopshere *Atmo = new Atmopshere;
	AtmosphereStruct Atmos;

	Float64 Altitude;

	DataLogger logAtmoTestData("AtmosphereTestData.txt", 25, " ");

	logAtmoTestData.add("Altitude", Altitude);
	logAtmoTestData.add("Rho", Atmos.rho);
	logAtmoTestData.add("Temperture", Atmos.Temperature);
	logAtmoTestData.add("Pressure", Atmos.Pressure);
	logAtmoTestData.add("SpeedOfSound", Atmos.speedOfSound);

	logAtmoTestData.printHeader();

	Atmo->initAtmosphere();
	for (Altitude = 0; Altitude < 10000; Altitude++) {
		Atmo->updateAtmosphere(Altitude, Atmos);
		logAtmoTestData.print();
	}

	std::cout << "Atmosphere Test done" << std::endl;
};

void AerodynamicTest()
{

	DataLogger logAeroTestData("AerodynamicTestData.txt", 25, " ");

	Aerodynamics * Aero = new Aerodynamics;
	Atmopshere * Atmo = new Atmopshere;
	readInData * readIn = new readInData;
	Transformation * transformation = new Transformation;

	AerodynamicStruct  AeroData;
	AircraftStruct     AircraftData;
	AtmosphereStruct   AtmoData;
	AirframeStruct  AirframeData;
	ThrustStruct  ThrustData;

	Float64 Altitude = 0.0;
	Float64 FlightTime = 0.0;

	Float64 psi = 0.0;
	Float64 theta = 0.0;
	Float64 phi = 0.0;

	AirframeData.rotRatesBody(0) = 0;
	AirframeData.rotRatesBody(1) = 0;
	AirframeData.rotRatesBody(2) = 0;

	AirframeData.Eta = 0;
	AirframeData.Xi = 0;
	AirframeData.Zeta = 0;

	AirframeData.matNEDToBody = transformation->MatNedToBody(phi, theta, psi);
	AirframeData.matBodyToNED = AirframeData.matNEDToBody.inverse();


	Eigen::Matrix3d matAeroToBody;

	// import data
	AircraftData.mass		= readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.wingarea	= readIn->readInParameter("wing_area", "Aircraft.txt");
	AircraftData.wingspan	= readIn->readInParameter("wing_span", "Aircraft.txt");
	AircraftData.MAC		= readIn->readInParameter("MAC", "Aircraft.txt");

	readIn->setPath("../Input/Aerodynamics/");
	Eigen::VectorXd AoA		= readIn->readInVector("AoA.txt");
	Eigen::VectorXd Mach	= readIn->readInVector("Ma.txt");
	Eigen::VectorXd Eta		= readIn->readInVector("Eta.txt");

	Aero->initAerodynamic(AeroData,AircraftData);
	Atmo->initAtmosphere();

	Float64 alpha;
	Float64 beta = 0.0;
	Eigen::Vector3d Velocity;

	std::ptrdiff_t i;

	// Define Output
	int a = AoA.size();
	int b = Mach.size();
	int c = Eta.maxCoeff(&i)/5+1;
	logAeroTestData.add("AoA size", a);
	logAeroTestData.add("Mach size", b);
	logAeroTestData.add("Eta size", c);
	
	
	logAeroTestData.add("CA", AeroData.CA);
	logAeroTestData.add("CM", AeroData.CM);
	logAeroTestData.add("CW", AeroData.CW);
	logAeroTestData.add("CZ", AeroData.CZ);
	logAeroTestData.add("CX", AeroData.CX);
	logAeroTestData.add("AoA [Deg]", AeroData.AoA);
	logAeroTestData.add("Mach [-]", AeroData.Mach);
	logAeroTestData.add("Eta [Deg]", AirframeData.Eta);

	logAeroTestData.printHeader();

	// constant altitude
	Atmo->updateAtmosphere(Altitude, AtmoData);

	for (int eta = 0; eta <= Eta.maxCoeff(&i); eta = eta + 5)
	{
		for (int CounterMach = 0; CounterMach < Mach.size(); CounterMach++) {

			Velocity(0) = Mach(CounterMach)*AtmoData.speedOfSound;
			Velocity(1) = 0;
			Velocity(2) = 0;

			for (int CounterAlpha = 0; CounterAlpha < AoA.size(); CounterAlpha++) {


				AirframeData.Eta = eta * PI / 180;

				alpha = AoA(CounterAlpha)*PI / 180;

				matAeroToBody = transformation->MatAeroToBody(alpha, beta);

				AirframeData.velBody = matAeroToBody * Velocity;

				AirframeData.velNED = AirframeData.matBodyToNED*AirframeData.velBody;

				Aero->updateAerodynamic(FlightTime,
					AtmoData,
					AeroData,
					AirframeData,
					ThrustData);

				logAeroTestData.print();
			}// end Eta loop


		}// end AoA Loop
	}// end Mach Loop
	
	std::cout << "Aerodynamic Test done" << std::endl;
};

void GuidanceTest()
{
	AerodynamicStruct  AeroData;
	AircraftStruct     AircraftData;
	AtmosphereStruct   AtmoData;
	AirframeStruct  AirframeData;
	ThrustStruct  ThrustData;
	GuidanceStruct GuidanceData;

	Guidance *guidanceTest = new Guidance;

	guidanceTest->initGuidance();

	guidanceTest->updateGuidance(0.0,
								AeroData,
								ThrustData,
								AircraftData,
								AirframeData,
								AtmoData, 
								GuidanceData);

}


int main()
{
	std::cout << "----------Module Test----------" << std::endl;
	AirframeStruct	AirframeData;
	FindNeighbor findNeighbor;
	MatFileReader test("../Autopilot.mat");

	matvar_t MatFileData = test.getMatFileInfo("AutopilotData");
	int Fields = MatFileData.dims[0] * MatFileData.dims[1];

	AutopilotStruct Autopilotdata;

	int start, stride, edge, copy_field = 0;
	start = 0;
	stride = 0;
	edge = 9;


	Autopilotdata.Alt = std::get<2>(test.readMatFileStructure("Alt", start, stride, edge, copy_field));
	Autopilotdata.Vel = std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
	Autopilotdata.x_bar = std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
	Autopilotdata.u_bar = std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));

	AirframeData.Eta = Autopilotdata.u_bar(1);
	AirframeData.posNED(2) = -Autopilotdata.Alt;
	AirframeData.velNED << Autopilotdata.Vel, 0, 0;
	AirframeData.StickPosition = Autopilotdata.u_bar(3);
	AirframeData.EulerAngles(1) = Autopilotdata.x_bar(1);
	findNeighbor.initFindNeighbor();
	findNeighbor.BlendingParameters(AirframeData);


	//AtmosphereTest();


	AerodynamicTest();
	//GuidanceTest();
	//AirframeStruct AirframeData;
	NavigationStruct NavData;
	IMUStruct IMUData;
	GuidanceStruct GuidanceData;


	IMU imutest;
	imutest.initIMU();
	imutest.updateIMU(0,AirframeData,IMUData);

	GPS gpstest;
	gpstest.initGPS();
	gpstest.updateGPS(0,NavData);
	
	Navigation testNav;
	testNav.initNavigation();
	testNav.updateNavigation(0, NavData, GuidanceData);

	system("pause");
}

