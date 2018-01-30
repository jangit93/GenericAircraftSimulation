#pragma once

#include<Eigen/dense>
#include"DataCloud.h"

class Neighbouring
{
public:
	Neighbouring();

	~Neighbouring();

	void	findNeighbour(AutopilotStruct &AutopilotData, 
						  AirframeStruct &AirframeData);
private:

};