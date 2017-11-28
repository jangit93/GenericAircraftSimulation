#include "BaseTrajectory.h"

BaseTrajectory::BaseTrajectory()
{
}

BaseTrajectory::~BaseTrajectory()
{
}

void BaseTrajectory::initTrajectory()
{
	this->initializeTrajectory();
}

void BaseTrajectory::updateTrajectory()
{
	this->calcTrajectory();
}

void BaseTrajectory::initializeTrajectory()
{
}

void BaseTrajectory::calcTrajectory()
{
}
