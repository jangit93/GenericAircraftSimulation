#include"Atmosphere.h"
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
	/*
	struct AutopilotData {
		double Alt;
		double Vel;
		Eigen::VectorXd u_bar;
		Eigen::VectorXd x_bar;
		Eigen::VectorXd Kx_pitch;
		double Ke_pitch;
		double Kv_pitch;
		double Kx_Vel;
		double Ke_Vel;
		Eigen::MatrixXd Kx_lat;
	};

	
	MatFileReader test("../Autopilot.mat");

	matvar_t MatFileData = test.getMatFileInfo("AutpilotData");
	int Fields = MatFileData.dims[0] * MatFileData.dims[1];

	AutopilotData * Autopilotdata = new AutopilotData[Fields];

	int start, stride, edge, copy_field = 0;
	edge = 9;
	
	for (start = 0; start < Fields; start++) {
	Autopilotdata[start].Alt		= std::get<2>(test.readMatFileStructure("Alt",start,stride,edge,copy_field));
	Autopilotdata[start].Vel		= std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
	Autopilotdata[start].x_bar		= std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
	Autopilotdata[start].u_bar		= std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));
	Autopilotdata[start].Kx_pitch	= std::get<1>(test.readMatFileStructure("Kx_pitch", start, stride, edge, copy_field));
	Autopilotdata[start].Ke_pitch	= std::get<2>(test.readMatFileStructure("Ke_pitch", start, stride, edge, copy_field));
	Autopilotdata[start].Kv_pitch	= std::get<2>(test.readMatFileStructure("Kv_pitch", start, stride, edge, copy_field));
	Autopilotdata[start].Kx_Vel		= std::get<2>(test.readMatFileStructure("Kx_Vel", start, stride, edge, copy_field));
	Autopilotdata[start].Ke_Vel		= std::get<2>(test.readMatFileStructure("Ke_Vel", start, stride, edge, copy_field));
	Autopilotdata[start].Kx_lat		= std::get<0>(test.readMatFileStructure("Kx_lat", start, stride, edge, copy_field)) ;				  
	}

	std::cout << "Alt" << "\t" << Autopilotdata[0].Alt				 << std::endl;
	std::cout << "Vel" << "\t" << Autopilotdata[0].Vel				 << std::endl;
	std::cout << "x_bar" << "\t" << Autopilotdata[0].x_bar.transpose()			 << std::endl;
	std::cout << "u_bar" << "\t" << Autopilotdata[0].u_bar.transpose() << std::endl;
	std::cout << "Kx_pitch" << "\t" << Autopilotdata[0].Kx_pitch	 << std::endl;
	std::cout << "Ke_pitch" << "\t" << Autopilotdata[0].Ke_pitch	 << std::endl;
	std::cout << "Kv_pitch" << "\t" << Autopilotdata[0].Kv_pitch	 << std::endl;
	std::cout << "Kx_Vel" << "\t" << Autopilotdata[0].Kx_Vel		 << std::endl;
	std::cout << "Ke_Vel" << "\t" << Autopilotdata[0].Ke_Vel		 << std::endl;
	std::cout << "Kx_lat" << std::endl << Autopilotdata[0].Kx_lat		 << std::endl;
	

	MatFileReader test2("../ADM.mat");
	std::cout << std::get<0>(test2.readMatFileData("C_A")) << std::endl;
	
	//AtmosphereTest();

	*/
	AerodynamicTest();
	//GuidanceTest();
	AirframeStruct AirframeData;
	NavigationStruct NavData;
	IMUStruct IMUData;
	GuidanceStruct GuidanceData;

	IMU imutest;
	imutest.initIMU();
	imutest.updateIMU(0,AirframeData,IMUData);

	GPS gpstest;
	gpstest.initGPS();
	gpstest.updateGPS(0,NavData);
	
	Navigation test;
	test.initNavigation();
	test.updateNavigation(0, NavData, GuidanceData);

	system("pause");
}

