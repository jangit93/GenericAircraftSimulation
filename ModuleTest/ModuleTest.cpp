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
#include"ODESolver.cpp"
#include"Trajectory.h"


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

void AerodynamicTest(SimDPreference &SimPref)
{

	DataLogger logAeroTestData("AerodynamicTestData.txt", 25, " ");
	Aerodynamics * Aero = new Aerodynamics(SimPref);
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

	Aero->initAerodynamic(FlightTime,AeroData,AircraftData);

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
	AtmoData.rho = 1.225;
	AtmoData.speedOfSound = 340;

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

void GuidanceTest(SimDPreference &SimPref)
{

	std::cout << "Guidance Test" << std::endl;
	AerodynamicStruct  AeroData;
	AircraftStruct     AircraftData;
	AtmosphereStruct   AtmoData;
	AirframeStruct  AirframeData;
	ThrustStruct  ThrustData;
	GuidanceStruct GuidanceData;

	AtmoData.rho = 1.225;
	AtmoData.speedOfSound = 340;

	AirframeData.velNED << 180, 0, 0;
	AirframeData.EulerAngles << 0, 0, 0;
	AirframeData.Xi = 0;
	AirframeData.Zeta = 0;
	AirframeData.Eta = 0;

	readInData *readIn = new readInData;
	DataLogger logGuidanceTestData("GuidanceTestData.txt", 25, " ");

	Aerodynamics *Aero = new Aerodynamics(SimPref);
	Float64 FlightTime = 0;
	Aero->initAerodynamic(FlightTime, AeroData, AircraftData);
	AircraftData.mass = readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.wingarea = readIn->readInParameter("wing_area", "Aircraft.txt");

	logGuidanceTestData.add("FlightTime", FlightTime);
	logGuidanceTestData.add("Phi_com", GuidanceData.Phi_com);
	logGuidanceTestData.add("Theta_com", GuidanceData.Theta_com);
	logGuidanceTestData.printHeader();

	AirframeData.Chi = 0;
	AirframeData.Gamma = 0;

	AirframeData.rotRatesBody << 0, 0, 0;
	Guidance *guidanceTest = new Guidance(SimPref);
	Transformation transform;
	guidanceTest->initGuidance(FlightTime,GuidanceData,AircraftData);

	AirframeData.matNEDToTraj = transform.MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);
	AirframeData.matNEDToBody = transform.MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));

	Aero->updateAerodynamic(FlightTime,
							AtmoData,
							AeroData,
							AirframeData,
							ThrustData);
	
	for (FlightTime = 0; FlightTime < 150/0.01; FlightTime++) {


		guidanceTest->updateGuidance(FlightTime,
									AeroData,
									ThrustData,
									AirframeData,
									GuidanceData);

		logGuidanceTestData.print();

		guidanceTest->logGuidanceData();
	}


	std::cout << "Guidance Test done" << std::endl;
}


void AutopilotTest()
{
	AirframeStruct	AirframeData;
	AerodynamicStruct AeroData;
	GuidanceStruct GuidanceData;

	
	StateController testController;

	testController.initStateController();

	MatFileReader test("../Autopilot.mat");

	matvar_t MatFileData = test.getMatFileInfo("AutopilotData");
	int Fields = MatFileData.dims[0] * MatFileData.dims[1];

	AutopilotStruct *Autopilotdata = new AutopilotStruct[Fields];;

	int start, stride, edge, copy_field = 0;
	start = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		Autopilotdata[start].Alt = std::get<2>(test.readMatFileStructure("Alt", start, stride, edge, copy_field));
		Autopilotdata[start].Vel = std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
		Autopilotdata[start].x_bar = std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		Autopilotdata[start].u_bar = std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));
	}
	AirframeData.Eta = Autopilotdata[1].u_bar(1);
	AirframeData.posNED(2) = -Autopilotdata[1].Alt;
	AirframeData.velNED << Autopilotdata[1].Vel, 0, 0;
	AirframeData.StickPosition = Autopilotdata[1].u_bar(3);
	AirframeData.EulerAngles(1) = Autopilotdata[1].x_bar(1);
	AeroData.Alpha = Autopilotdata[1].x_bar(1);
	AeroData.Beta = 0;
	AirframeData.EulerAngles(0) = 0;

	AirframeData.rotRatesBody.setZero();
	GuidanceData.Theta_com = Autopilotdata[1].x_bar(1);
	GuidanceData.Velocity_com = 180;
	GuidanceData.Beta_com = 0;
	GuidanceData.Phi_com = 0;

	testController.updateStateController(0, AirframeData, AeroData, GuidanceData);
	/*findNeighbor.initFindNeighbor();
	findNeighbor.BlendingParameters(AirframeData);*/
}

void IMUTest(SimDPreference &SimPref)
{

	AirframeStruct AirframeData;
	IMUStruct IMUData;

	IMU *imutest = new IMU(SimPref);
	imutest->initIMU();
	imutest->updateIMU(0, AirframeData, IMUData);

	std::cout << "IMU Test Done" << std::endl;
}

void GPSTest(SimDPreference &SimPref)
{
	NavigationStruct NavData;
	

	GPS *gpstest = new GPS(SimPref);
	gpstest->initGPS();
	gpstest->updateGPS(0, NavData);

	std::cout << "GPS Test Done" << std::endl;
}

void NavigationTest(SimDPreference &SimPref)
{
	NavigationStruct NavData;
	GuidanceStruct GuidanceData;

	Navigation *testNav = new Navigation(SimPref);
	testNav->initNavigation();
	testNav->updateNavigation(0, NavData, GuidanceData);

	std::cout << "Navigation Test Done" << std::endl;
}


void TrajectoryTest(SimDPreference &SimPref)
{
	
	Trajectory *Test = new Trajectory(SimPref);
	Atmopshere *Atmo = new Atmopshere;
	Transformation *Trafo = new Transformation;
	Float64				FlightTime = 0;
	AtmosphereStruct	AtmoData;
	AerodynamicStruct	AeroData;
	AirframeStruct		AirframeData;
	ThrustStruct		ThrustData;
	AircraftStruct		AircraftData;
	GuidanceStruct		GuidamceData;

	MatFileReader test("../Autopilot.mat");
	


	matvar_t MatFileData = test.getMatFileInfo("AutopilotData");
	int Fields = MatFileData.dims[0] * MatFileData.dims[1];

	AutopilotStruct * AutopilotData = new AutopilotStruct[Fields];

	int start, stride, edge, copy_field = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		AutopilotData[start].Alt = std::get<2>(test.readMatFileStructure("Alt", start, stride, edge, copy_field));
		AutopilotData[start].Vel = std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
		AutopilotData[start].x_bar = std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		AutopilotData[start].u_bar = std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));
	}
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;
	IMUStruct IMUData;



	Test->initTrajectory(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData,
						GuidamceData,
						NavData,
						ActuatorData,
						IMUData);

	Atmo->initAtmosphere();

	AirframeData.Eta = AutopilotData[1].u_bar(1);
	AirframeData.posNED(2) = -AutopilotData[1].Alt;
	AirframeData.velNED << AutopilotData[1].Vel, 0, 0;
	AirframeData.StickPosition = AutopilotData[1].u_bar(3);
	AirframeData.EulerAngles(1) = AutopilotData[1].x_bar(1);
	GuidamceData.Theta_com = AirframeData.EulerAngles(1);

	std::cout << "----------------------------------------------" << std::endl;
	Float64 dt = 0.01;
	for(FlightTime = 0.01;FlightTime < 150;FlightTime+=0.01){

	AirframeData.velNED = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, dt);
	AirframeData.posNED = EulerIntegration(AirframeData.posNED, AirframeData.velNED, dt);

	AirframeData.rotRatesBody = EulerIntegration(AirframeData.rotRatesBody, AirframeData.accRotBody, dt);
	AirframeData.EulerAngles = EulerIntegration(AirframeData.EulerAngles, AirframeData.Eulerdot, dt);

	AirframeData.Gamma = atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(1)*AirframeData.velNED(1)));


	AirframeData.Chi = atan2(AirframeData.velNED(1), AirframeData.velNED(0));

	AirframeData.matNEDToBody = Trafo->MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo->MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);

	Atmo->updateAtmosphere(AirframeData.posNED(2), AtmoData);


	Test->updateTrajectory(FlightTime,
							AtmoData,
							AeroData,
							AirframeData,
							ThrustData,
							GuidamceData,
							NavData,
							ActuatorData,
							IMUData);

	}



}

int main()
{
	std::cout << "----------Module Test----------" << std::endl;
	
	SimDPreference SimPref;
	SimPref.AeroMode = 1;
	SimPref.GuidanceMode = 2;
	SimPref.IMUMode = 1;
	SimPref.GPSMode = 1;
	SimPref.NavMode = 1;
	SimPref.Trajectory = 2;
	SimPref.EngineMode = 1;
	/*
	AtmosphereTest();


	AerodynamicTest(SimPref);
	
	

	IMUTest(SimPref);
	GPSTest(SimPref);
	NavigationTest(SimPref);
	*/
	//AutopilotTest();
	//GuidanceTest(SimPref);

	TrajectoryTest(SimPref);

	system("pause");
}

