#include "FindNeighbor.h"

FindNeighbor::FindNeighbor()
{
}

FindNeighbor::~FindNeighbor()
{
	
}

void FindNeighbor::initFindNeighbor()
{
	MatFileReader readNeighborData("../Autopilot.mat");

	MatFileData = readNeighborData.getMatFileInfo("AutopilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	neighbors = new AutopilotStruct[Fields];

	start, stride, edge, copy_field = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		neighbors[start].Alt = std::get<2>(readNeighborData.readMatFileStructure("Alt", start, stride, edge, copy_field));
		neighbors[start].Vel = std::get<2>(readNeighborData.readMatFileStructure("Vel", start, stride, edge, copy_field));
		neighbors[start].AltVec = std::get<3>(readNeighborData.readMatFileStructure("AltVec", start, stride, edge, copy_field));
		neighbors[start].VelVec = std::get<3>(readNeighborData.readMatFileStructure("VelVec", start, stride, edge, copy_field));

		/*
		std::cout << "Alt" << "\t" << SchedulingPara[start].Alt << "\n" << std::endl;
		std::cout << "Vel" << "\t" << SchedulingPara[start].Vel << "\n" << std::endl;
		std::cout << "x_bar" << "\t" << SchedulingPara[start].x_bar << "\n" << std::endl;
		std::cout << "u_bar" << "\t" << SchedulingPara[start].u_bar << "\n" << std::endl;
		std::cout << "Kx_pitch" << "\t" << SchedulingPara[start].Kx_pitch << "\n" << std::endl;
		std::cout << "Ke_pitch" << "\t" << SchedulingPara[start].Ke_pitch << "\n" << std::endl;
		std::cout << "Kv_pitch" << "\t" << SchedulingPara[start].Kv_pitch << "\n" << std::endl;
		std::cout << "Kx_Vel" << "\t" << SchedulingPara[start].Kx_Vel << "\n" << std::endl;
		std::cout << "Ke_Vel" << "\t" << SchedulingPara[start].Ke_Vel << "\n" << std::endl;
		std::cout << "Kx_lat" << "\t" << SchedulingPara[start].Kx_lat << "\n" << std::endl;
		*/
	}
}



Eigen::Vector4d FindNeighbor::BlendingParameters(AirframeStruct & AirframeData)
{
	
	// find neighbours altitude
	std::cout << neighbors[0].AltVec.size() << std::endl;
	for (int i = 0; i < neighbors[0].AltVec.size() - 1; i++) {
		std::cout << -AirframeData.posNED(2) << neighbors[0].AltVec(i + 1) << -AirframeData.posNED(2) << neighbors[0].AltVec(i) - 10 <<  std::endl;
		if (-AirframeData.posNED(2) < neighbors[0].AltVec(i + 1) && -AirframeData.posNED(2) >= neighbors[0].AltVec(i) - 10) {

			tempAlt << i, i + 1;

			minAlt = neighbors[1].AltVec(i);
			maxAlt = neighbors[0].AltVec(i + 1);
			break;
		}
	}

	// find neighbours velocity
	for (int i = 0; i < neighbors[0].VelVec.size() - 1; i++) {
		if (AirframeData.velNED.norm() < neighbors[0].VelVec(i + 1) && AirframeData.velNED.norm() >= neighbors[0].VelVec(i) - 10) {
			
			tempVel << i, i + 1;

			minVel = neighbors[0].VelVec(i);
			maxVel = neighbors[0].VelVec(i + 1);
			break;
		}
	}

	//calculate blending parameters
	Neighbor = combineVec(tempAlt, tempVel);
	std::cout << Neighbor << std::endl;
	
	for (int i = 0; i < Neighbor.rows(); i++) {

		int m, n;
		m = Neighbor(i, 0);
		n = Neighbor(i, 1);
		xi(0) = (-AirframeData.posNED(2) - neighbors[n*MatFileData.dims[0]+m].Alt) / (maxAlt - minAlt);

		phi_j(0) = 1 - xi(0)*xi(0)*(3-2* abs(xi(0)));

		xi(1) = (AirframeData.velNED.norm() - neighbors[n*MatFileData.dims[0] + m].Vel) / (maxVel - minVel);

		phi_j(1) = 1 - xi(1)*xi(1)*(3-2 * abs(xi(1)));

		phi(i) = phi_j(0)*phi_j(1);
	}

	return phi;
	std::cout << phi << std::endl;
}

Eigen::MatrixXd FindNeighbor::combineVec(Eigen::Vector2d & Alt, Eigen::Vector2d & Vel)
{
	comb.resize(Alt.size()*Vel.size(), 2);
	
	Vec1.resize(Alt.size()*Alt.size());
	Vec1 << Alt, Alt;

	Vec2.resize(Vel.size()*Vel.size());

	for (int ii = 0; ii <Vel.size(); ii++) {
		Vec2(ii) = Vel(0);
		Vec2(ii + 2) = Vel(1);
	}

	comb << Vec1, Vec2;
	
	return comb;
}
