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

	/// 1) get controller for every trim point in grid
	MatFileReader readAutopilotData("../Input/Autopilot.mat");

	MatFileData = readAutopilotData.getMatFileInfo("AutopilotData");
	Fields = MatFileData.dims[0] * MatFileData.dims[1];

	StateControllertData = new AutopilotStruct[Fields];

	copy_field = 0;
	start = 0;
	stride = 0;
	edge = 9;

	for (start = 0; start < Fields; start++) {
		StateControllertData[start].Alt			= std::get<2>(readAutopilotData.readMatFileStructure("Alt", start, stride, edge, copy_field));
		StateControllertData[start].Vel			= std::get<2>(readAutopilotData.readMatFileStructure("Vel", start, stride, edge, copy_field));
		StateControllertData[start].x_bar		= std::get<1>(readAutopilotData.readMatFileStructure("x_bar", start, stride, edge, copy_field));
		StateControllertData[start].u_bar		= std::get<1>(readAutopilotData.readMatFileStructure("u_bar", start, stride, edge, copy_field));
		StateControllertData[start].Kx_pitch	= std::get<3>(readAutopilotData.readMatFileStructure("Kx_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Ke_pitch	= std::get<2>(readAutopilotData.readMatFileStructure("Ke_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Kv_pitch	= std::get<2>(readAutopilotData.readMatFileStructure("Kv_pitch", start, stride, edge, copy_field));
		StateControllertData[start].Kx_Vel		= std::get<2>(readAutopilotData.readMatFileStructure("Kx_Vel", start, stride, edge, copy_field));
		StateControllertData[start].Ke_Vel		= std::get<2>(readAutopilotData.readMatFileStructure("Ke_Vel", start, stride, edge, copy_field));
		StateControllertData[start].Kx_lat		= std::get<0>(readAutopilotData.readMatFileStructure("Kx_lat", start, stride, edge, copy_field));
		StateControllertData[start].Ke_lat		= std::get<0>(readAutopilotData.readMatFileStructure("Ke_lat", start, stride, edge, copy_field));
		StateControllertData[start].AltVec		= std::get<3>(readAutopilotData.readMatFileStructure("AltVec", start, stride, edge, copy_field));
		StateControllertData[start].VelVec		= std::get<3>(readAutopilotData.readMatFileStructure("VelVec", start, stride, edge, copy_field));
	}

	findneighbor->initFindNeighbor();

	/// 2) initialise parameters
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
	Delta_x_lat.resize(6);

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
											GuidanceStruct &GuidanceData, 
										    ActuatorStruct &ActuatorData, 
											IMUStruct &IMUData, 
											NavigationStruct &NavData)
{
	/// 1) find neighbors in grid
	PHI			<< std::get<0>(findneighbor->BlendingParameters(NavData));
	NEIGHBOR	<< std::get<1>(findneighbor->BlendingParameters(NavData));

	/// 2) get control input from guidance
	theta_com	= GuidanceData.Theta_com;
	phi_com		= GuidanceData.Phi_com;
	Vel_com		= GuidanceData.Velocity_com;
	beta_com	=  GuidanceData.Beta_com;

	//longitude
	x_long_pitch << IMUData.rotRatesBody(1), AeroData.Alpha, NavData.EulerAngles(1);
	//latitude
	x_lat << IMUData.rotRatesBody(2), AeroData.Beta, IMUData.rotRatesBody(0), NavData.EulerAngles(0);

	/// 3) calculate control variable for every grid neighbor
	for (int i = 0; i < NEIGHBOR.rows(); i++) {

	
		index = sub2ind(NEIGHBOR(i, 0), NEIGHBOR(i, 1), MatFileData.dims[0], MatFileData.dims[1]);
		x_0 = StateControllertData[index].x_bar;
	
		u_0 = StateControllertData[index].u_bar;


		K_lat << StateControllertData[index].Kx_lat,
				 StateControllertData[index].Ke_lat;

		K_long_pitch << StateControllertData[index].Kx_pitch,
						StateControllertData[index].Ke_pitch;

		K_v = StateControllertData[index].Kv_pitch;


		K_long_vel << StateControllertData[index].Kx_Vel,
					  StateControllertData[index].Ke_Vel;

	

		//longitude
		x_0_pitch << x_0(4), x_0(1), x_0(7);


		delta_x_long = x_long_pitch - x_0_pitch;


		e2_long = e2_long + dt * (theta_com - NavData.EulerAngles(1));


		delta_x_vel = NavData.velNED.norm() - x_0(0);

		e1_long = e1_long + dt * (Vel_com - NavData.velNED.norm());


		//latitude
		x_0_lat << x_0(5), x_0(2), x_0(3), x_0(6);


		delta_x_lat = x_lat - x_0_lat;


		e1_lat = e1_lat + dt * (beta_com - AeroData.Beta);
		e2_lat = e2_lat + dt * (phi_com - NavData.EulerAngles(0));

		e_lat << e1_lat, e2_lat;


		
		Delta_x_long << delta_x_long, e2_long;
		delta_u_long = -K_long_pitch * Delta_x_long+K_v * (theta_com - NavData.EulerAngles(1));

		Delta_x_vel << delta_x_vel, e1_long;
		delta_u_vel = -K_long_vel * Delta_x_vel;


		Delta_x_lat << delta_x_lat, e_lat;
		delta_u_lat = -K_lat * Delta_x_lat;


		u_sched_eta(i)		= delta_u_long + u_0(1);
		u_sched_delta(i)	= delta_u_vel + u_0(3);
		u_sched_zeta(i)		= delta_u_lat(1) + u_0(2);
		u_sched_xi(i)		= delta_u_lat(0) + u_0(0);
	}
	
	if (abs(PHI.dot(u_sched_eta)) >= 29.99*PI / 180)
	{
		ActuatorData.Eta = sign(abs(PHI.dot(u_sched_eta)))*29.99*PI / 180;
	}
	else {
		ActuatorData.Eta = PHI.dot(u_sched_eta);
	}

	/// 4) blending 
	
	ActuatorData.Delta = PHI.dot(u_sched_delta);
	ActuatorData.Xi = PHI.dot(u_sched_xi);
	ActuatorData.Zeta = PHI.dot(u_sched_zeta);

}

int StateController::sub2ind(const int row, const int column, const int rows,const int columns)
{
	return row * (columns-1) + column;
}

int StateController::sign(Float64 val)
{
	return (val>0) ? 1 : ((val<0) ? -1 : 0);
}
