#include "Aircraft.h"


Aircraft::Aircraft(SimDPreference &SimPref)
{
	trajectory = new Trajectory(SimPref);
	Atmo = new Atmopshere;
	
	TotalSimTime = SimPref.TotalSimTime;
	dt = SimPref.dt;
	FlightTime = 0;
	
}

Aircraft::~Aircraft()
{

}


void Aircraft::simulateAircraft()
{
	/// 1) Read in trim points for initialization
	MatFileReader trim("../Input/Autopilot.mat");

	matvar_t MatFileData = trim.getMatFileInfo("AutopilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	TrimPoints = new AutopilotStruct[Fields];

	
	start = 0;
	copy_field = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		TrimPoints[start].Alt = std::get<2>(trim.readMatFileStructure("Alt", start, stride, edge, copy_field));
		TrimPoints[start].Vel = std::get<2>(trim.readMatFileStructure("Vel", start, stride, edge, copy_field));
		TrimPoints[start].x_bar = std::get<1>(trim.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		TrimPoints[start].u_bar = std::get<1>(trim.readMatFileStructure("u_bar", start, stride, edge, copy_field));
	}

	/// 2) initialize atmosphere and aircraft
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

	
	/// 3) set trim point
	ActuatorData.Eta = TrimPoints[1].u_bar(1);
	ActuatorData.Delta = TrimPoints[1].u_bar(3);

	AirframeData.posNED(2) = -TrimPoints[1].Alt;
	NavData.posNED(2) = AirframeData.posNED(2);

	AirframeData.velNED << TrimPoints[1].Vel, 0, 0;
	NavData.velNED = AirframeData.velNED;

	AirframeData.EulerAngles(1) = TrimPoints[1].x_bar(1);
	NavData.EulerAngles(1) = AirframeData.EulerAngles(1);

	GuidanceData.Theta_com = NavData.EulerAngles(1);

	NavData.dt = dt;
	IMUData.dt = dt;
	GuidanceData.reshape = 1/dt;
	time1 = 0.0;
	tstart = clock();
	std::cout << "----------------------------------------------" << std::endl;
	
	
	/// 4) simulate aircraft (calculate trajectory)

		//#pragma loop( hint_parallel(90))
		//#pragma omp parallel
		for (FlightTime = 0.0; FlightTime < TotalSimTime; FlightTime += dt) {

			Atmo->updateAtmosphere(NavData.posNED(2), AtmoData);
			
			//#pragma omp master
			trajectory->updateTrajectory(FlightTime,
										AtmoData,
										AeroData,
										AirframeData,
										ThrustData,
										GuidanceData, 
										NavData, 
										ActuatorData, 
										IMUData);
		

		}
	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulation TIme = " << time1 << " sec." << std::endl;


}