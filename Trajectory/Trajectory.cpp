#include "Trajectory.h"

Trajectory::Trajectory()
{
	int a = 2;
	selectTrajectory(a);

	initTrajectory();
}

Trajectory::~Trajectory()
{
}

void Trajectory::selectTrajectory(int type)
{
	switch (type)
	{
	case 1:
		traj = new BaseTrajectory;
		break;
	case 2:
		traj = new Trajectory3Dof;
		break;
	}
}

void Trajectory::initTrajectory()
{
	traj->initTrajectory();
}

void Trajectory::updateTrajectory()
{
	traj->updateTrajectory();
}
