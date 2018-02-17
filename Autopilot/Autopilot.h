#pragma once
#include"MatFileReader.h"
#include"DataCloud.h"
#include"StateController.h"
#include"FindNeighbor.h"

class Autopilot
{
public: 
	Autopilot();

	~Autopilot();

	void initAutopilot();

	void updateAutopilot();

private:
	StateController *controller;
	FindNeighbor *neigh;

};