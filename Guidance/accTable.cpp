#include "accTable.h"

accTable::accTable()
{
	LogGuidanceData = new DataLogger("GuidanceData.txt", 25, " ");
}

accTable::~accTable()
{
}

void accTable::initGuidance(Float64 &FlightTime, GuidanceStruct &GuidanceData, AircraftStruct &AircraftData)
{
	MatFileReader readAccTable("../Input/accTable.mat");

	AccTable = std::get<0>(readAccTable.readMatFileData("accTable"));

	s_x	= AccTable.row(0);
	s_y = AccTable.row(1);
	s_z = AccTable.row(2);

	v_x	= AccTable.row(3);
	v_y	= AccTable.row(4);
	v_z	= AccTable.row(5);
		 
	a_x_com = AccTable.row(6);
	a_y_com = AccTable.row(7);
	a_z_com = AccTable.row(8);
		
		mass = AircraftData.mass;
		wingarea = AircraftData.wingarea;

		initLogGuidance(FlightTime, GuidanceData);

	
}

void accTable::updateGuidance(Float64 FlightTime, 
							AerodynamicStruct & AeroData, 
							ThrustStruct & ThrustData, 
							AirframeStruct & AirframeData, 
							GuidanceStruct &GuidanceData)
{
	Float64 flightTime = FlightTime * 100;
	accNED << a_x_com(flightTime), a_y_com(flightTime), a_z_com(flightTime) + GRAVITATIONAL_CONSTANT;
	velNED << v_x(flightTime), v_y(flightTime), v_z(flightTime);

	accTraj = AirframeData.matNEDToTraj*accNED;
	accBody = AirframeData.matNEDToBody* accNED;
	velBody = AirframeData.matNEDToBody*velNED;

	GuidanceData.Velocity_com = sqrt(v_x(flightTime)*v_x(flightTime) + v_y(flightTime) * v_y(flightTime) + v_z(flightTime) * v_z(flightTime));


	 Alpha_com = -(accBody(2)*mass) / (AeroData.C_zdalpha*AeroData.q_bar*wingarea )+ AeroData.C_A0 / AeroData.C_zdalpha;
	 Beta_com  = 0.0;

	chi_dot = accTraj(1) / GuidanceData.Velocity_com;

	//help functions
	
	Float64	G = (chi_dot*AirframeData.velNED.norm()) / GRAVITATIONAL_CONSTANT;
	Float64 a = 1 - G * tan(Alpha_com)*sin(AeroData.Beta);
	Float64 b = AirframeData.Gamma / cos(AeroData.Beta);
	Float64 c = 1 + G * G*cos(AeroData.Beta)*cos(AeroData.Beta);

	GuidanceData.Phi_com = atan(G * (cos(AeroData.Beta) / cos(Alpha_com)) * (a - b * b + b * tan(Alpha_com)*sqrt(c*(1 - b * b) + G * G*sin(AeroData.Beta)*sin(AeroData.Beta))) / 
							(a*a - b * b*(1 + c * tan(Alpha_com)*tan(Alpha_com))));

	Float64 a1 = cos(Alpha_com) * cos(AeroData.Beta);
	Float64 b1 = sin(AeroData.Beta)*sin(GuidanceData.Phi_com) + sin(Alpha_com) * cos(AeroData.Beta)*cos(GuidanceData.Phi_com);

	GuidanceData.Theta_com = atan((a1*b1 + sin(AeroData.Beta)*sqrt(a1*a1 - sin(AeroData.Beta)*sin(AeroData.Beta) + b1 * b1)) / (a1*a1 - sin(AeroData.Beta)*sin(AeroData.Beta)));

	GuidanceData.acc_com << a_x_com(flightTime),a_y_com(flightTime),a_z_com(flightTime);
	GuidanceData.Vel_com << v_x(flightTime), v_y(flightTime), v_z(flightTime);
	GuidanceData.Pos_com << s_x(flightTime), s_y(flightTime), s_z(flightTime);
}

void accTable::initLogGuidance(Float64 &FlightTime, GuidanceStruct & GuidanceData)
{
	LogGuidanceData->add("Flighttime [s]", FlightTime);
	LogGuidanceData->add("accBody_com_x", GuidanceData.acc_com(0));
	LogGuidanceData->add("accBody_com_", GuidanceData.acc_com(1));
	LogGuidanceData->add("accBody_com_z", GuidanceData.acc_com(2));
	LogGuidanceData->add("Vel_com_x", GuidanceData.Vel_com(0));
	LogGuidanceData->add("Vel_com_y", GuidanceData.Vel_com(1));
	LogGuidanceData->add("Vel_com_z", GuidanceData.Vel_com(2));
	LogGuidanceData->add("Pos_x", GuidanceData.Pos_com(0));
	LogGuidanceData->add("Pos_y", GuidanceData.Pos_com(1));
	LogGuidanceData->add("Pos_z", GuidanceData.Pos_com(2));
	LogGuidanceData->add("Phi_com [rad]", GuidanceData.Phi_com);
	LogGuidanceData->add("Theta_com [rad]", GuidanceData.Theta_com);
	LogGuidanceData->printHeader();
}

void accTable::logGuidanceData()
{
	LogGuidanceData->print();
}
