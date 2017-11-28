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

		tstart = clock();              // start 

		int i = 1;

		std::cout << "Aircraft Simulation" << std::endl;
		Float64 FlightTime = 1;
		AtmosphereStruct  AtmoData;
		AerodynamicStruct  AeroData;
		AirframeStruct  AirframeData;
		ThrustStruct  ThrustData;
		AircraftStruct AircraftData;

		Trajectory Test;
		Test.initTrajectory();
		Test.updateTrajectory(FlightTime,
								AtmoData,
								AeroData,
								AirframeData,
								ThrustData);

	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}