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

void Trajectory3Dof::calcTrajectory()
{
	std::cout << "update 3Dof Trajectory" << std::endl;
}
