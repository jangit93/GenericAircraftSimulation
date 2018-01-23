#include"MatFileReader.h"


int main()
{
	MatFileReader test("Autopilot.mat");
	/*
	std::cout << std::get<2>(test.readMatFileStructure("Alt","AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Vel", "AutpilotData")) << std::endl;

	std::cout << std::get<1>(test.readMatFileStructure("u_bar", "AutpilotData")) << std::endl;
	std::cout << std::get<1>(test.readMatFileStructure("x_bar", "AutpilotData")) << std::endl;
	std::cout << std::get<1>(test.readMatFileStructure("Kx_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Ke_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Kv_pitch", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Kx_Vel", "AutpilotData")) << std::endl;
	std::cout << std::get<2>(test.readMatFileStructure("Ke_Vel", "AutpilotData")) << std::endl;
	*/
	std::cout << std::get<0>(test.readMatFileStructure("Kx_lat", "AutpilotData")) << std::endl;
	MatFileReader test2("ADM.mat");
	std::cout << std::get<0>(test2.readMatFileData("C_A")) << std::endl;
	
	system("pause");
}