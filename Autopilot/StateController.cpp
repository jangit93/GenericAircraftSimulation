#include "StateController.h"

StateController::StateController()
{
}

StateController::~StateController()
{
}

void StateController::initStateController()
{
	MatFileReader readAutopilotData("../Autopilot.mat");

	MatFileData = readAutopilotData.getMatFileInfo("AutpilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	GainSchedulingStruct * SchedulingPara = new GainSchedulingStruct[Fields];

	start, stride, edge, copy_field = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		SchedulingPara[start].Alt		= std::get<2>(readAutopilotData.readMatFileStructure("Alt", start, stride, edge, copy_field));
		SchedulingPara[start].Vel		= std::get<2>(readAutopilotData.readMatFileStructure("Vel", start, stride, edge, copy_field));
		SchedulingPara[start].x_bar		= std::get<1>(readAutopilotData.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		SchedulingPara[start].u_bar		= std::get<1>(readAutopilotData.readMatFileStructure("u_bar", start, stride, edge, copy_field));
		SchedulingPara[start].Kx_pitch	= std::get<1>(readAutopilotData.readMatFileStructure("Kx_pitch", start, stride, edge, copy_field));
		SchedulingPara[start].Ke_pitch	= std::get<2>(readAutopilotData.readMatFileStructure("Ke_pitch", start, stride, edge, copy_field));
		SchedulingPara[start].Kv_pitch	= std::get<2>(readAutopilotData.readMatFileStructure("Kv_pitch", start, stride, edge, copy_field));
		SchedulingPara[start].Kx_Vel	= std::get<2>(readAutopilotData.readMatFileStructure("Kx_Vel", start, stride, edge, copy_field));
		SchedulingPara[start].Ke_Vel	= std::get<2>(readAutopilotData.readMatFileStructure("Ke_Vel", start, stride, edge, copy_field));
		SchedulingPara[start].Kx_lat	= std::get<0>(readAutopilotData.readMatFileStructure("Kx_lat", start, stride, edge, copy_field));


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

	}
}

void StateController::updateStateController()
{
}
