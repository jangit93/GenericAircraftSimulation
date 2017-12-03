#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include"Engine.h"
#include<Map>
#include<math.h>
#include <iostream>
#include <time.h> 
#include"Aerodynamic.h"
#include"Airframe.h"
#include"Trajectory.h"


int main(int argv, char* argc[])
{
	double time1 = 0.0, tstart;      // time measurment variable

//#pragma omp parallel 
		tstart = clock();              // start 

		LinearInterpolation test;
		readInData test1;
		test1.setPath("../Input/Aerodynamics/");
	Eigen:VectorXd Cmq = test1.readInVector("CMQ.txt");
		std::cout << Cmq << std::endl;
		Eigen::VectorXd Ma = test1.readInVector("Ma.txt");
		std::cout << Ma << std::endl;
		Float64 a = test.linearInterpolation(Ma,Cmq,0.21);
		std::cout << a << std::endl;
		system("pause");
		int i = 1;

		std::cout << "---------Aircraft Simulation----------" << std::endl;
		Float64 FlightTime = 1;
		AtmosphereStruct	AtmoData;
		AerodynamicStruct	AeroData;
		AirframeStruct		AirframeData;
		ThrustStruct		ThrustData;
		AircraftStruct		AircraftData;
		AutopilotStruct		AutpilotData;
		GuidanceStruct		GuidamceData;

		Trajectory *Test = new Trajectory;
		Test->initTrajectory(AeroData,
							AirframeData,
							ThrustData,
							AircraftData,
							AutpilotData,
							GuidamceData);
		std::cout << "--------------------------------------" << std::endl;
		system("pause");
		Test->updateTrajectory(FlightTime,
								AtmoData,
								AeroData,
								AirframeData,
								ThrustData, 
								AutpilotData,
								GuidamceData);

	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}