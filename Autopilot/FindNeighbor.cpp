#include "FindNeighbor.h"

FindNeighbor::FindNeighbor()
{
}

FindNeighbor::~FindNeighbor()
{
	
}

void FindNeighbor::initFindNeighbor()
{
	MatFileReader readNeighborData("../Input/Autopilot.mat");

	MatFileData = readNeighborData.getMatFileInfo("AutopilotData");
	Fields		= MatFileData.dims[0] * MatFileData.dims[1];

	neighbors = new AutopilotStruct[Fields];

	copy_field = 0;
	start = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		neighbors[start].Alt	= std::get<2>(readNeighborData.readMatFileStructure("Alt", start, stride, edge, copy_field));
		neighbors[start].Vel	= std::get<2>(readNeighborData.readMatFileStructure("Vel", start, stride, edge, copy_field));
		neighbors[start].AltVec = std::get<3>(readNeighborData.readMatFileStructure("AltVec", start, stride, edge, copy_field));
		neighbors[start].VelVec = std::get<3>(readNeighborData.readMatFileStructure("VelVec", start, stride, edge, copy_field));
	}
}



std::tuple<Eigen::Vector4d, Eigen::MatrixXd> FindNeighbor::BlendingParameters(NavigationStruct &NavData)
{
	
	for (int i = 0; i < neighbors[0].AltVec.size()-1 ; i++) {
		if ((-NavData.posNED(2)) <= neighbors[0].AltVec(i+1) && -NavData.posNED(2) >= neighbors[0].AltVec(i) - 10) {
			tempAlt << i, i+1;

			minAlt = neighbors[0].AltVec(i);
			maxAlt = neighbors[0].AltVec(i + 1);
			break;
		}
	}

	for (int i = 0; i < neighbors[0].VelVec.size() - 1; i++) {
		if (NavData.velNED.norm() < neighbors[0].VelVec(i+1) && NavData.velNED.norm() >= neighbors[0].VelVec(i) - 10) {
			
			tempVel << i, i+1;

			minVel = neighbors[0].VelVec(i);
			maxVel = neighbors[0].VelVec(i + 1);
			break;
		}
	}

	//calculate blending parameters
	Neighbor = combineVec(tempAlt, tempVel);

	for (int i = 0; i < Neighbor.rows(); i++) {

		int index = sub2ind(Neighbor(i, 0), Neighbor(i, 1), MatFileData.dims[0], MatFileData.dims[1]);

		xi(0) = (-NavData.posNED(2) - neighbors[index].Alt) / (maxAlt - minAlt);

		phi_j(0) = 1 - xi(0)*xi(0)*(3-2* abs(xi(0)));

		xi(1) = (NavData.velNED.norm() - neighbors[index].Vel) / (maxVel - minVel);

		phi_j(1) = 1 - xi(1)*xi(1)*(3-2 * abs(xi(1)));

		phi(i) = phi_j(0)*phi_j(1);
	}

	return std::make_tuple(phi,Neighbor);
	
}

Eigen::MatrixXd FindNeighbor::combineVec(Eigen::Vector2d & Alt, Eigen::Vector2d & Vel)
{
	comb.resize(Alt.size()*Vel.size(), 2);
	
	comb << Alt(0),Vel(0),Alt(1),Vel(0),Alt(0),Vel(1),Alt(1),Vel(1); 

	return comb;
}

int FindNeighbor::sub2ind(const int row, const int column, const int rows, const int columns)
{
	return row * (columns - 1) + column;
}
