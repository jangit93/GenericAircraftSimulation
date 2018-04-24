#include "StateController.h"

StateController::StateController()
{
	findneighbor = new FindNeighbor;
	
}

StateController::~StateController()
{
}

void StateController::initStateController()
{
	MatFileReader readAutopilotData("../Autopilot.mat");

	MatFileData = readAutopilotData.getMatFileInfo("AutopilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	StateControllertData = new AutopilotStruct[Fields];

	start, stride, edge, copy_field = 0;
	start = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		StateControllertData[start].Alt = std::get<2>(readAutopilotData.readMatFileStructure("Alt", start, stride, edge, copy_field));
		StateControllertData[start].Vel = std::get<2>(readAutopilotData.readMatFileStructure("Vel", start, stride, edge, copy_field));
		StateControllertData[start].x_bar = std::get<1>(readAutopilotData.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		StateControllertData[start].u_bar = std::get<1>(readAutopilotData.readMatFileStructure("u_bar", start, stride, edge, copy_field));
		StateControllertData[start].Kx_pitch = std::get<3>(readAutopilotData.readMatFileStructure("Kx_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Ke_pitch = std::get<2>(readAutopilotData.readMatFileStructure("Ke_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Kv_pitch = std::get<2>(readAutopilotData.readMatFileStructure("Kv_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Kx_Vel = std::get<2>(readAutopilotData.readMatFileStructure("Kx_Vel", start, stride, edge, copy_field));
		StateControllertData[start].Ke_Vel = std::get<2>(readAutopilotData.readMatFileStructure("Ke_Vel", start, stride, edge, copy_field));
		StateControllertData[start].Kx_lat = std::get<0>(readAutopilotData.readMatFileStructure("Kx_lat", start, stride, edge, copy_field));
		StateControllertData[start].Ke_lat = std::get<0>(readAutopilotData.readMatFileStructure("Ke_lat", start, stride, edge, copy_field));
		StateControllertData[start].AltVec = std::get<3>(readAutopilotData.readMatFileStructure("AltVec", start, stride, edge, copy_field));
		StateControllertData[start].VelVec = std::get<3>(readAutopilotData.readMatFileStructure("VelVec", start, stride, edge, copy_field));

		
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

	findneighbor->initFindNeighbor();

	//initialise parameters
	x_0.resize(9, 1);
	u_0.resize(4, 1);
	K_lat.resize(2, 6);
	
	K_long_vel.resize(1, 2);
	
	x_long_pitch.resize(3, 1);
	x_0_pitch.resize(3, 1);
	delta_x_long.resize(3, 1);

	x_lat.resize(4, 1);
	x_0_lat.resize(4, 1);
	delta_x_lat.resize(4, 1);
	e_lat.resize(2, 1);

	x_0.setZero();
	u_0.setZero();
	K_lat.setZero();
	K_long_pitch.setZero();
	K_long_vel.setZero();

	x_long_pitch.setZero();
	x_0_pitch.setZero();
	delta_x_long.setZero();

	x_lat.setZero();
	x_0_lat.setZero();
	delta_x_lat.setZero();
	e_lat.setZero();

	delta_u_long = 0;
	delta_u_vel = 0;
	delta_u_lat << 0,0;


	e1_long = 0;
	e2_long = 0;
	e1_lat = 0;
	e2_lat = 0;
	
	dt = 0.01;
	NEIGHBOR.resize(4, 2);
}

void StateController::updateStateController(Float64 FlightTime,
											AirframeStruct &AirframeData,
											AerodynamicStruct &AeroData,
											GuidanceStruct &GuidanceData)
{
	PHI << std::get<0>(findneighbor->BlendingParameters(AirframeData));
	NEIGHBOR << std::get<1>(findneighbor->BlendingParameters(AirframeData));
	//std::cout << NEIGHBOR << std::endl;
	//NEIGHBOR << 0, 0, 1, 0, 0, 1, 1, 1;//std::get<1>(findneighbor->BlendingParameters(AirframeData));

	//Eigen::RowVector4d PHI = PHI.transpose();
	theta_com = GuidanceData.Theta_com;
	phi_com = GuidanceData.Phi_com;
	Vel_com = 180;//GuidanceData.Velocity_com;
	beta_com =  0;// GuidanceData.Beta_com;

	for (int i = 0; i < NEIGHBOR.rows(); i++) {

		//gains
		int index = sub2ind(NEIGHBOR(i, 0), NEIGHBOR(i, 1), MatFileData.dims[0], MatFileData.dims[1]);
		x_0 = StateControllertData[index].x_bar;
		//std::cout << x_0 << std::endl;
		//std::cout << std::endl;
		u_0 = StateControllertData[index].u_bar;
		//std::cout << u_0 << std::endl;
		//std::cout << std::endl;

		K_lat << StateControllertData[index].Kx_lat,
				 StateControllertData[index].Ke_lat;
		//std::cout << K_lat << std::endl;
		//std::cout << std::endl;
		K_long_pitch << StateControllertData[index].Kx_pitch,
						StateControllertData[index].Ke_pitch;
		//std::cout << K_long_pitch << std::endl;
		//std::cout << std::endl;
		K_v = StateControllertData[index].Kv_pitch;
		//std::cout << K_v << std::endl;
		//std::cout << std::endl;

		K_long_vel << StateControllertData[index].Kx_Vel,
					  StateControllertData[index].Ke_Vel;

		//std::cout << K_long_vel << std::endl;
		//std::cout << std::endl;

		//longitude
		x_long_pitch << AirframeData.rotRatesBody(1), AeroData.Alpha, AirframeData.EulerAngles(1);
		//std::cout << x_long_pitch << std::endl;
		//std::cout << std::endl;
		
		x_0_pitch << x_0(4), x_0(1), x_0(7);
		//std::cout << x_0_pitch << std::endl;
		//std::cout << std::endl;

		delta_x_long = x_long_pitch - x_0_pitch;
		//std::cout << delta_x_long << std::endl;
		//std::cout << std::endl;

		e2_long = e2_long + dt * (theta_com - AirframeData.EulerAngles(1));
		//std::cout << e2_long << std::endl;
		//std::cout << std::endl;
		/*if (FlightTime >= 40 && i ==0)
		{
			std::cout << x_long_pitch << std::endl;
			std::cout << std::endl;
			std::cout << x_0_pitch << std::endl;
			std::cout << std::endl;
			std::cout << delta_x_long << std::endl;
			std::cout << std::endl;
			std::cout << e2_long << std::endl;
			std::cout << std::endl;
			std::cout << delta_x_long << std::endl;

		}*/

		delta_x_vel = AirframeData.velNED.norm() - x_0(0);
		//std::cout << delta_x_vel << std::endl;
		//std::cout << std::endl;

		e1_long = e1_long + dt * (Vel_com - AirframeData.velNED.norm());
		//std::cout << e1_long << std::endl;
		//std::cout << std::endl;

		//latitude
		x_lat << AirframeData.rotRatesBody(2), AeroData.Beta, AirframeData.rotRatesBody(0), AirframeData.EulerAngles(0);
		//std::cout << x_lat << std::endl;
		//std::cout << std::endl;

		x_0_lat << x_0(5), x_0(2), x_0(3), x_0(6);
		//std::cout << x_0_lat << std::endl;
		//std::cout << std::endl;

		delta_x_lat = x_lat - x_0_lat;
		//std::cout << delta_x_lat << std::endl;
		//std::cout << std::endl;

		e1_lat = e1_lat + dt * (beta_com - AeroData.Beta);
		e2_lat = e2_lat + dt * (phi_com - AirframeData.EulerAngles(0));

		e_lat << e1_lat, e2_lat;
		//std::cout << e_lat << std::endl;
		//std::cout << std::endl;

		Delta_x_lat.resize(6);
		Delta_x_long << delta_x_long, e2_long;
		delta_u_long = -K_long_pitch * Delta_x_long+K_v * (theta_com - AirframeData.EulerAngles(1));
		//std::cout << delta_u_long << std::endl;
		//std::cout << std::endl;

		Delta_x_vel << delta_x_vel, e1_long;
		delta_u_vel = -K_long_vel * Delta_x_vel;
		//std::cout << delta_u_vel << std::endl;
		//std::cout << std::endl;

		Delta_x_lat << delta_x_lat, e_lat;
		delta_u_lat = -K_lat * Delta_x_lat;
		//std::cout << delta_u_lat << std::endl;
		//std::cout << std::endl;

		u_sched_eta(i)		= delta_u_long + u_0(1);
		u_sched_delta(i)	= delta_u_vel + u_0(3);
		u_sched_zeta(i)		= delta_u_lat(1) + u_0(2);
		u_sched_xi(i)		= delta_u_lat(0) + u_0(0);
	}
	Float64 Eta = PHI.dot(u_sched_eta);
	if (abs(Eta) >= 29.99*PI / 180)
	{
		Eta = sign(Eta)*29.99*PI / 180;
	}
	AirframeData.Eta = Eta;//PHI.dot(u_sched_eta);
	AirframeData.StickPosition	= PHI.dot(u_sched_delta);
	AirframeData.Xi				= PHI.dot(u_sched_xi);
	AirframeData.Zeta			= PHI.dot(u_sched_zeta);
	/*
	std::cout << AirframeData.Eta << std::endl;
	std::cout << AirframeData.StickPosition << std::endl;
	std::cout << AirframeData.Xi << std::endl;
	std::cout << AirframeData.Zeta << std::endl;*/
	
}

int StateController::sub2ind(const int row, const int column, const int rows,const int columns)
{
	return row * (columns-1) + column;
}

int StateController::sign(Float64 val)
{
	return (val>0) ? 1 : ((val<0) ? -1 : 0);
}
