/** @defgroup	Moduletest Moduletest
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	ModuleTest.cpp cotains module tests for several modules. 
*	Some modules need a complete simulation to be tested 
*  @{
*/

#include<iostream>
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
#include"ODESolver.cpp"
#include"Trajectory.h"
#include"Actuator.h"
#include<omp.h>
#include<ctime>
#include"Aircraft.h"


/**
* \brief The atmospheric model is tested. Hence altitude is increased up to
*		 10000m. Atmospheric data is stored and plotted in Matlab. The plots
		 are compared to characteritic trends.
*/
void AtmosphereTest()
{
	
	/// 1) Initialization of models and data
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

	/// 2) Loop increases altitude; data is stored to outputfile
	for (Altitude = 0; Altitude < 10000; Altitude++) {
		Atmo->updateAtmosphere(Altitude, Atmos);
		logAtmoTestData.print();
	}

	std::cout << "Atmosphere Test done" << std::endl;
};

/**
* \brief Datcom aerodynamic is tested. Therefor a windtunnel is simulate. Within loops 
		 Angle of attack, elevator angle and mach are varied. Characterisitcs (e.g. drag polar) 
		 are calculated for several flight states. Only longitudinal aerodynamic is tested.
*/
void AerodynamicTest(SimDPreference &SimPref)
{

	/// 1) Initialization of models and data
	DataLogger logAeroTestData("AerodynamicTestData.txt", 25, " ");
	Aerodynamics * Aero = new Aerodynamics(SimPref);
	readInData * readIn = new readInData;
	Transformation * transformation = new Transformation;

	AerodynamicStruct  AeroData;
	AircraftStruct     AircraftData;
	AtmosphereStruct   AtmoData;
	AirframeStruct  AirframeData;
	ThrustStruct  ThrustData;
	IMUStruct IMUData;
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;

	Float64 Altitude   = 0.0;
	Float64 FlightTime = 0.0;

	Eigen::Matrix3d matAeroToBody;
	Float64 psi   = 0.0;
	Float64 theta = 0.0;
	Float64 phi   = 0.0;

	IMUData.rotRatesBody(0) = 0;
	IMUData.rotRatesBody(1) = 0;
	IMUData.rotRatesBody(2) = 0;

	ActuatorData.Eta  = 0;
	ActuatorData.Xi   = 0;
	ActuatorData.Zeta = 0;

	AirframeData.matNEDToBody = transformation->MatNedToBody(phi, theta, psi);
	AirframeData.matBodyToNED = AirframeData.matNEDToBody.inverse();


	/// 2) aircraft characterisitcs and simulation data are read in 
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

	/// 3) Definition of Output
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
	logAeroTestData.add("Eta [Deg]", ActuatorData.Eta);

	logAeroTestData.printHeader();

	// constant altitude
	AtmoData.rho = 1.225;
	AtmoData.speedOfSound = 340;


	/// 4) 3 loops simulate a wind tunnel with varying flight states
	for (int eta = 0; eta <= Eta.maxCoeff(&i); eta = eta + 5)
	{
		for (int CounterMach = 0; CounterMach < Mach.size(); CounterMach++) {

			Velocity(0) = Mach(CounterMach)*AtmoData.speedOfSound;
			Velocity(1) = 0;
			Velocity(2) = 0;

			for (int CounterAlpha = 0; CounterAlpha < AoA.size(); CounterAlpha++) {


				ActuatorData.Eta = eta * PI / 180;

				alpha = AoA(CounterAlpha)*PI / 180;

				matAeroToBody = transformation->MatAeroToBody(alpha, beta);

				AirframeData.velBody = matAeroToBody * Velocity;

				NavData.velNED = AirframeData.matBodyToNED*AirframeData.velBody;

				Aero->updateAerodynamic(FlightTime,
					AtmoData,
					AeroData,
					AirframeData,
					ThrustData,
					ActuatorData,
					IMUData,
					NavData);

				logAeroTestData.print();
			}// end Eta loop


		}// end AoA Loop
	}// end Mach Loop
	
	std::cout << "Aerodynamic Test done" << std::endl;
};

void GuidanceTest(SimDPreference &SimPref)
{

	std::cout << "Guidance Test" << std::endl;
	readInData *readIn = new readInData;
	DataLogger logGuidanceTestData("GuidanceTestData.txt", 25, " ");
	Aerodynamics *Aero = new Aerodynamics(SimPref);
	Guidance *guidanceTest = new Guidance(SimPref);
	Transformation transform;

	Float64 FlightTime = 0;
	AerodynamicStruct  AeroData;
	AircraftStruct     AircraftData;
	AtmosphereStruct   AtmoData;
	AirframeStruct  AirframeData;
	ThrustStruct  ThrustData;
	GuidanceStruct GuidanceData;
	IMUStruct IMUData;
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;

	AtmoData.rho = 1.225;
	AtmoData.speedOfSound = 340;

	NavData.velNED << 180, 0, 0;
	AirframeData.velNED << 180, 0, 0;
	NavData.EulerAngles << 0, 0, 0;
	ActuatorData.Xi   = 0;
	ActuatorData.Zeta = 0;
	ActuatorData.Eta  = 0;


	Aero->initAerodynamic(FlightTime, AeroData, AircraftData);
	AircraftData.mass = readIn->readInParameter("mass", "Aircraft.txt");
	AircraftData.wingarea = readIn->readInParameter("wing_area", "Aircraft.txt");

	logGuidanceTestData.add("FlightTime", FlightTime);
	logGuidanceTestData.add("Phi_com", GuidanceData.Phi_com);
	logGuidanceTestData.add("Theta_com", GuidanceData.Theta_com);
	logGuidanceTestData.printHeader();

	AirframeData.Chi = 0;
	AirframeData.Gamma = 0;

	IMUData.rotRatesBody << 0, 0, 0;

	guidanceTest->initGuidance(FlightTime,GuidanceData,AircraftData);

	AirframeData.matNEDToTraj = transform.MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);
	AirframeData.matNEDToBody = transform.MatNedToBody(NavData.EulerAngles(0), NavData.EulerAngles(1), NavData.EulerAngles(2));

	Aero->updateAerodynamic(FlightTime,
							AtmoData,
							AeroData,
							AirframeData,
							ThrustData,
							ActuatorData,
							IMUData,
							NavData);
	
	for (FlightTime = 0; FlightTime < 150; FlightTime++) {
			

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

/*
void AutopilotTest()
{
	AirframeStruct	AirframeData;
	AerodynamicStruct AeroData;
	GuidanceStruct GuidanceData;
	IMUStruct IMUData;
	NavigationStruct NavData;
	ActuatorStruct ActuatorData;

	
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
	ActuatorData.Eta = Autopilotdata[1].u_bar(1);
	NavData.posNED(2) = -Autopilotdata[1].Alt;
	NavData.velNED << Autopilotdata[1].Vel, 0, 0;
	ActuatorData.Delta = Autopilotdata[1].u_bar(3);
	NavData.EulerAngles(1) = Autopilotdata[1].x_bar(1);
	AeroData.Alpha = Autopilotdata[1].x_bar(1);
	AeroData.Beta = 0;
	NavData.EulerAngles(0) = 0;

	IMUData.rotRatesBody.setZero();
	GuidanceData.Theta_com = Autopilotdata[1].x_bar(1);
	GuidanceData.Velocity_com = 180;
	GuidanceData.Beta_com = 0;
	GuidanceData.Phi_com = 0;

	testController.updateStateController(0, AirframeData, AeroData, GuidanceData, ActuatorData, IMUData, NavData);
	findNeighbor.initFindNeighbor();
	findNeighbor.BlendingParameters(AirframeData);
}*/

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
	AirframeStruct AirframeData;

	GPS *gpstest = new GPS(SimPref);
	gpstest->initGPS();
	gpstest->updateGPS(0, NavData,AirframeData);

	std::cout << "GPS Test Done" << std::endl;
}

void NavigationTest(SimDPreference &SimPref)
{
	NavigationStruct NavData;
	AirframeStruct AirframeData;

	Navigation *testNav = new Navigation(SimPref);
	testNav->initNavigation();
	testNav->updateNavigation(0, NavData, AirframeData);

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
	double time1 = 0.0, tstart;
	tstart = clock();
	std::cout << "----------------------------------------------" << std::endl;
	Float64 dt = 0.01;

	{
		
		for (FlightTime = 0.01; FlightTime < 150; FlightTime += 0.01) {

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

	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;


}

void ActuatorTest(SimDPreference &SimPref)
{
	Float64 FlightTime = 0;
	ActuatorStruct ActuatorData;
	AirframeStruct AirframeData;
	Actuator * actuator = new Actuator(SimPref);

	actuator->initActuator(FlightTime, AirframeData, ActuatorData);

	actuator->updateActuator(FlightTime, AirframeData, ActuatorData);

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
	SimPref.ActuatorMode = 1;
	
	AtmosphereTest();

	AerodynamicTest(SimPref);
	
	GuidanceTest(SimPref);

	//TrajectoryTest(SimPref);
	
/*
	IMUTest(SimPref);
	GPSTest(SimPref);
	NavigationTest(SimPref);
	
	AutopilotTest();

	ActuatorTest(SimPref);

	*/
	system("pause");
}
/**@}*/