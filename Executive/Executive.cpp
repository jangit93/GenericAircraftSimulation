#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include"Engine.h"
#include<Map>
#include<math.h>
#include <iostream>
#include<ctime>
#include"Aerodynamic.h"
#include"Airframe.h"
#include"Trajectory.h"
#include"ODESolver.cpp"
#include"Transformation.h"

int main(int argv, char* argc[])
{
	double time1 = 0.0, tstart;      // time measurment variable

//#pragma omp parallel 
		tstart = clock();              // start 


		std::cout << "---------Aircraft Simulation----------" << std::endl;
		Trajectory *Test = new Trajectory;
		Atmopshere *Atmo = new Atmopshere;
		Transformation *Trafo = new Transformation;
		Float64				FlightTime = 1;
		AtmosphereStruct	AtmoData;
		AerodynamicStruct	AeroData;
		AirframeStruct		AirframeData;
		ThrustStruct		ThrustData;
		AircraftStruct		AircraftData;
		GuidanceStruct		GuidamceData;

		MatFileReader test("../Autopilot.mat");

		matvar_t MatFileData = test.getMatFileInfo("AutopilotData");
		int Fields = MatFileData.dims[0] * MatFileData.dims[1];

		AutopilotStruct * AutopilotData = new AutopilotStruct[Fields];

		int start, stride, edge, copy_field = 0;
		stride = 0;
		edge = 9;

		for (start = 0; start < Fields; start++) {
			AutopilotData[start].Alt = std::get<2>(test.readMatFileStructure("Alt", start, stride, edge, copy_field));
			AutopilotData[start].Vel = std::get<2>(test.readMatFileStructure("Vel", start, stride, edge, copy_field));
			AutopilotData[start].x_bar = std::get<1>(test.readMatFileStructure("x_bar", start, stride, edge, copy_field));
			AutopilotData[start].u_bar = std::get<1>(test.readMatFileStructure("u_bar", start, stride, edge, copy_field));
			AutopilotData[start].Kx_pitch = std::get<1>(test.readMatFileStructure("Kx_pitch", start, stride, edge, copy_field));
			AutopilotData[start].Ke_pitch = std::get<2>(test.readMatFileStructure("Ke_pitch", start, stride, edge, copy_field));
			AutopilotData[start].Kv_pitch = std::get<2>(test.readMatFileStructure("Kv_pitch", start, stride, edge, copy_field));
			AutopilotData[start].Kx_Vel = std::get<2>(test.readMatFileStructure("Kx_Vel", start, stride, edge, copy_field));
			AutopilotData[start].Ke_Vel = std::get<2>(test.readMatFileStructure("Ke_Vel", start, stride, edge, copy_field));
			AutopilotData[start].Kx_lat = std::get<0>(test.readMatFileStructure("Kx_lat", start, stride, edge, copy_field));
			AutopilotData[start].Ke_lat = std::get<0>(test.readMatFileStructure("Ke_lat", start, stride, edge, copy_field));
		}



		
		Test->initTrajectory(AeroData,
							AirframeData,
							ThrustData,
							AircraftData,
							*AutopilotData,
							GuidamceData);

		Atmo->initAtmosphere();

		AirframeData.Eta = AutopilotData[0].u_bar(1);
		AirframeData.posNED(2) = -AutopilotData[0].Alt;
		AirframeData.velNED(0) = AutopilotData[0].Vel;
		AirframeData.StickPosition = AutopilotData[0].u_bar(3);
		AirframeData.EulerAngles(1) = AutopilotData[0].x_bar(1);
		std::cout << "--------------------------------------" << std::endl;
		system("pause");

		AirframeData.velNED			 = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, 0.01);
		AirframeData.posNED			 = EulerIntegration(AirframeData.posNED, AirframeData.velNED, 0.01);
		AirframeData.rotRatesBody	 = EulerIntegration(AirframeData.rotRatesBody, AirframeData.accRotBody,0.01);
		AirframeData.EulerAngles	 = EulerIntegration(AirframeData.EulerAngles, AirframeData.Eulerdot, 0.01);

		AirframeData.Gamma = atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(0)*AirframeData.velNED(0)));

		AirframeData.Chi = atan2(AirframeData.velNED(1), AirframeData.velNED(0));

		AirframeData.matNEDToBody = Trafo->MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
		AirframeData.matBodyToNED = Trafo->MatBodyToNED(AirframeData.matNEDToBody);
		AirframeData.matNEDToTraj = Trafo->MatBodyToTrajectory(AirframeData.Gamma, AirframeData.Chi);

		Atmo->updateAtmosphere(AirframeData.posNED(2), AtmoData);
		Test->updateTrajectory(FlightTime,
								AtmoData,
								AeroData,
								AirframeData,
								ThrustData, 
								*AutopilotData,
								GuidamceData);

	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}