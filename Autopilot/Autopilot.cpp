#include "Autopilot.h"

Autopilot::Autopilot()
{

}

Autopilot::~Autopilot()
{
}


void Autopilot::initAutopilot()
{
	controller = new StateController;
	neigh = new FindNeighbor;

	
}

void Autopilot::updateAutopilot()
{
	
}
