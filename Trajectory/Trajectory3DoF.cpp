#include "Trajectory3DoF.h"

Trajectory3Dof::Trajectory3Dof()
{
	engine = new Engine;
	aerodynamics = new Aerodynamics;

}

Trajectory3Dof::~Trajectory3Dof()
{
}

void Trajectory3Dof::initializeTrajectory()
{
	engine->initEngine();
	aerodynamics->initAerodynamic();
	std::cout << "init 3Dof Trajectory" << std::endl;
}

void Trajectory3Dof::calcTrajectorythis(Float64 FlightTime,	
										AtmosphereStruct & AtmoData, 
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData, 
										ThrustStruct & ThrustData)
{
	std::cout << "update 3Dof Trajectory" << std::endl;
}


