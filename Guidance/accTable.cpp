#include "accTable.h"

accTable::accTable()
{
}

accTable::~accTable()
{
}

void accTable::initializeGuidance()
{
	MatFileReader readAccTable("../accTable.mat");

	AccTable = std::get<0>(readAccTable.readMatFileData("accTable"));

		Eigen::RowVectorXd s_x 	   = AccTable.row(0);
		Eigen::RowVectorXd s_y	   = AccTable.row(1);
		Eigen::RowVectorXd s_z	   = AccTable.row(2);
		Eigen::RowVectorXd v_x	   = AccTable.row(3);
		Eigen::RowVectorXd v_y	   = AccTable.row(4);
		Eigen::RowVectorXd v_z	   = AccTable.row(5);
		Eigen::RowVectorXd a_x_com = AccTable.row(6);
		Eigen::RowVectorXd a_y_com = AccTable.row(7);
		Eigen::RowVectorXd a_z_com = AccTable.row(8);
		
		Vec_fg << 0, 0, GRAVITATIONAL_CONSTANT;

}

void accTable::calcGuidance(Float64 FlightTime, 
							AerodynamicStruct & AeroData, 
							ThrustStruct & ThrustData, 
							AircraftStruct & AircraftData, 
							AirframeStruct & AirframeData, 
							AtmosphereStruct & AtmosphereData,
							GuidanceStruct &GuidanceData)
{
	GuidanceData.Velocity_com = sqrt(v_x(FlightTime)*v_x(FlightTime) + v_y(FlightTime) * v_y(FlightTime) + v_z(FlightTime) * v_z(FlightTime));

	AeroData.q_bar;
}
