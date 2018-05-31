/** @defgroup	Executive Executive
*	@author		Jan Olucak
*	@date		10.05.2018
*	@version	1.0
*
*	This file executes the actual simulation. The prefered models are read in. Aircraft class is initalized. The Trajectory is calculated
*  @{
*/

#ifndef EXECUTIVE__H
#define EXECUTIVE__H


#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include"Engine.h"
#include<Map>
#include<math.h>
#include <iostream>
#include<ctime>
#include"Aerodynamic.h"
#include"Airframe.h"
#include"Aircraft.h"

int main(int argv, char* argc[])
{
	//initalization
	Float32 time1;  
	SimDPreference SimPref;
	readInData SimulationData;
	

	std::cout << "-------------Aircraft Simulation-------------" << std::endl;

	SimPref.AeroMode		= SimulationData.readInParameter("AeroModel", "Simulation.dat");
	SimPref.GuidanceMode	= SimulationData.readInParameter("GuidanceModel", "Simulation.dat");
	SimPref.IMUMode			= SimulationData.readInParameter("ImuModel", "Simulation.dat");
	SimPref.GPSMode			= SimulationData.readInParameter("GpsModel", "Simulation.dat");;
	SimPref.NavMode			= SimulationData.readInParameter("NavigationModel", "Simulation.dat");;
	SimPref.Trajectory		= SimulationData.readInParameter("Trajectory", "Simulation.dat");;
	SimPref.EngineMode		= SimulationData.readInParameter("EngineModel", "Simulation.dat");
	SimPref.ActuatorMode	= SimulationData.readInParameter("ActuatorModel", "Simulation.dat");
	SimPref.dt				= SimulationData.readInParameter("time_step", "Simulation.dat");
	SimPref.TotalSimTime	= SimulationData.readInParameter("Simulation_Time", "Simulation.dat");

	Aircraft *testAircraft = new Aircraft(SimPref);

	time1 = 0.0;
	

	std::clock_t c_start = std::clock();

	testAircraft->simulateAircraft();

	std::clock_t c_end = std::clock();

	double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
	std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";
	system("Pause");

}
/**@}*/
#endif	EXECUTIVE__H