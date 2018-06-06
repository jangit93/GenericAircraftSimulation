#include "Trajectory.h"

Trajectory::Trajectory(SimDPreference &SimPref)
{
	selectTrajectory(SimPref.Trajectory,SimPref);

}

Trajectory::~Trajectory()
{
}

void Trajectory::selectTrajectory(int type,
								  SimDPreference &SimPref)
{
	switch (type)
	{
	case 1:
		std::cout << "Trajectory:\t"<< "3 Degrees of Freedom" << std::endl;
		traj = new Trajectory3Dof(SimPref);
		break;

	case 2:
		std::cout << "Trajectory:\t"<<"6 Degrees of Freedom" << std::endl;
		traj = new Trajectory6Dof(SimPref);
		break;

	case 3 :
		std::cout << "Trajectory:\t" << "Real System Trajectory" << std::endl;
		traj = new RealSystemTrajectory(SimPref);
		break;

	}
}



void Trajectory::updateTrajectory(Float64 FlightTime, 
								  AtmosphereStruct & AtmoData, 
								  AerodynamicStruct & AeroData, 
								  AirframeStruct & AirframeData, 
								  ThrustStruct & ThrustData,
								  GuidanceStruct & GuidanceData,
									NavigationStruct &NavData,
									ActuatorStruct &ActuatorData,
									IMUStruct &IMUData)
{
	traj->updateTrajectory(FlightTime,
						   AtmoData,
						   AeroData, 
						   AirframeData, 
						   ThrustData,
						   GuidanceData,NavData,ActuatorData,IMUData);
}

void Trajectory::initTrajectory(Float64 &FlightTime, 
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData, 
								ThrustStruct & ThrustData, 
								AircraftStruct & AircraftData,
								GuidanceStruct & GuidanceData,
								NavigationStruct &NavData,
								ActuatorStruct &ActuatorData,
								IMUStruct &IMUData)
{
	
	traj->initTrajectory(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData,
						GuidanceData,
						NavData,
						ActuatorData,
						IMUData);
}

void Trajectory::logTraj()
{
	traj->logTraj();
}
