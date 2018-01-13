#include "Trajectory.h"

Trajectory::Trajectory()
{
	int a = 1;
	selectTrajectory(a);

}

Trajectory::~Trajectory()
{
}

void Trajectory::selectTrajectory(int type)
{
	switch (type)
	{
	case 1:
		std::cout << "Trajectory: Trajectory 3Dof" << std::endl;
		traj = new Trajectory3Dof;
		break;

	case 2:
		std::cout << "Trajectory: Trajectory 6Dof" << std::endl;
		break;

	}
}



void Trajectory::updateTrajectory(Float64 FlightTime, 
								  AtmosphereStruct & AtmoData, 
								  AerodynamicStruct & AeroData, 
								  AirframeStruct & AirframeData, 
								  ThrustStruct & ThrustData, 
								  AutopilotStruct & AutopilotData,
								  GuidanceStruct & GuidanceData)
{
	traj->updateTrajectory(FlightTime,
						   AtmoData,
						   AeroData, 
						   AirframeData, 
						   ThrustData,
						   AutopilotData,
						   GuidanceData);
}

void Trajectory::initTrajectory(AerodynamicStruct & AeroData, 
								AirframeStruct & AirframeData, 
								ThrustStruct & ThrustData, 
								AircraftStruct & AircraftData, 
								AutopilotStruct & AutopilotData, 
								GuidanceStruct & GuidanceData)
{
	traj->initTrajectory(AeroData,
						AirframeData,
						ThrustData,
						AircraftData,
						AutopilotData,
						GuidanceData);
}


