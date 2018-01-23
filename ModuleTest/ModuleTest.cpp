#include"Atmosphere.h"
#include"Aerodynamic.h"
#include"DataLogger.h"
#include"readInData.h"
#include"MatFileReader.h"
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

	AirframeData.matNEDToBody << cos(psi) * cos(theta), sin(psi) * cos(theta), -sin(phi),
		cos(psi)*sin(theta)*sin(phi) - sin(psi)*cos(phi), sin(psi)*sin(theta)*sin(phi) + cos(psi)*cos(phi), cos(theta)*sin(phi),
		cos(psi)*sin(theta)*cos(phi) + sin(psi)*sin(phi), sin(psi)*sin(theta)*cos(phi) - cos(psi)*sin(phi), cos(theta)*cos(phi);

	AirframeData.matBodyToNED = AirframeData.matNEDToBody.inverse();
	Eigen::Matrix3d matAeroToBody;

	// import data
	AircraftData.mass		= readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.wingarea	= readIn->readInParameter("wing_area", "Aircraft.txt");
	AircraftData.wingspan	= readIn->readInParameter("wing_span", "Aircraft.txt");

	readIn->setPath("../Input/Aerodynamics/");
	Eigen::VectorXd AoA		= readIn->readInVector("AoA.txt");
	Eigen::VectorXd Mach	= readIn->readInVector("Ma.txt");
	Eigen::VectorXd Eta		= readIn->readInVector("Eta.txt");

	Aero->initAerodynamic(AeroData,AircraftData);
	Atmo->initAtmosphere();

	Float64 alpha;
	Float64 beta = 0.0;
	Eigen::Vector3d Velocity;


	// Define Output
	logAeroTestData.add("AoA [Deg]", AeroData.AoA);
	logAeroTestData.add("Mach [-]", AeroData.Mach);
	logAeroTestData.add("Eta [Deg]", AirframeData.Eta);
	logAeroTestData.add("CA", AeroData.CA);

	logAeroTestData.printHeader();

	// constant altitude
	Atmo->updateAtmosphere(Altitude, AtmoData);
	
	for (int eta = 0; eta <= 30; eta = eta + 5)
	{
		for (int CounterMach = 0; CounterMach < Mach.size(); CounterMach++){
			
				 Velocity(0) = Mach(CounterMach)*AtmoData.speedOfSound;
				 Velocity(1) = 0;
				 Velocity(2) = 0;

			

				for (int CounterAlpha = 0; CounterAlpha < AoA.size(); CounterAlpha++) {

				
					AirframeData.Eta =  eta*PI / 180;
					
					alpha = AoA(CounterAlpha)*PI / 180;

					matAeroToBody << cos(alpha)*cos(beta), -cos(alpha)*sin(beta), -sin(alpha),
						sin(beta), cos(beta), 0,
						sin(alpha)*cos(beta), -sin(alpha)*sin(beta), cos(alpha);

					AirframeData.velBody = matAeroToBody*Velocity;

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


int main()
{
	std::cout << "----------Module Test----------" << std::endl;

	MatFileReader test("../Autopilot.mat");
	/*
	std::cout << std::get<2>(test.readMatFileStructure("Alt","AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Vel", "AutpilotData")) << std::endl;

	std::cout << std::get<1>(test.readMatFileStructure("u_bar", "AutpilotData")) << std::endl;
	std::cout << std::get<1>(test.readMatFileStructure("x_bar", "AutpilotData")) << std::endl;
	std::cout << std::get<1>(test.readMatFileStructure("Kx_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Ke_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Kv_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Kx_Vel", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Ke_Vel", "AutpilotData")) << std::endl;
	*/
	std::cout << std::get<0>(test.readMatFileStructure("Kx_lat", "AutpilotData")) << std::endl;
	MatFileReader test2("../ADM.mat");
	std::cout << std::get<0>(test2.readMatFileData("C_A")) << std::endl;

	//AtmosphereTest();

	//AerodynamicTest();

	system("pause");
}

