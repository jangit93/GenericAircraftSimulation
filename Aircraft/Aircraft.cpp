#include "Aircraft.h"
#include<omp.h>

Aircraft::Aircraft(SimDPreference &SimPref)
{
	trajectory = new Trajectory(SimPref);
	Atmo = new Atmopshere;
	
	FlightTime = 0;
	
}

Aircraft::~Aircraft()
{
}

void Aircraft::initAircraft()
{


}

void Aircraft::simulateAircraft()
{
	MatFileReader test("../Autopilot.mat");

	matvar_t MatFileData = test.getMatFileInfo("AutopilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	TrimPoints = new AutopilotStruct[Fields];

	int start, stride, edge, copy_field = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		TrimPoints[start].Alt = std::get<2>(test.readMatFileStructure("Alt", start, stride, edge, copy_field));
		TrimPoints[start].Vel = std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
		TrimPoints[start].x_bar = std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		TrimPoints[start].u_bar = std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));
	}

	
	Atmo->initAtmosphere();

	trajectory->initTrajectory(FlightTime,
								AeroData,
								AirframeData,
								ThrustData,
								AircraftData,
								GuidanceData,
								NavData,
								ActuatorData,
								IMUData);

	AirframeData.Eta = TrimPoints[1].u_bar(1);
	AirframeData.posNED(2) = -TrimPoints[1].Alt;
	AirframeData.velNED << TrimPoints[1].Vel, 0, 0;
	AirframeData.StickPosition = TrimPoints[1].u_bar(3);
	AirframeData.EulerAngles(1) = TrimPoints[1].x_bar(1);
	GuidanceData.Theta_com = AirframeData.EulerAngles(1);

	double time1 = 0.0, tstart;
	tstart = clock();
	std::cout << "----------------------------------------------" << std::endl;
	Float64 dt = 0.01;

	#pragma loop(hint_parallel(2))
	for (FlightTime = 0.0; FlightTime < 150; FlightTime += 0.01) {

		Atmo->updateAtmosphere(AirframeData.posNED(2), AtmoData);

		trajectory->updateTrajectory(FlightTime,
			AtmoData,
			AeroData,
			AirframeData,
			ThrustData,
			GuidanceData, NavData, ActuatorData, IMUData);

		//trajectory->logTraj();
	}
	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulation TIme = " << time1 << " sec." << std::endl;


}
