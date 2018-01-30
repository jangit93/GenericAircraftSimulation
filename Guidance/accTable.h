#pragma once
#include<Eigen/dense>
#include<iostream>
#include"../DataCloud/DataCloud.h"
#include"../Tools/IndependetDataTypes.h"
#include"BaseGuidance.h"
#include"../Tools/MatFileReader.h"
#include"../Tools/Constants.h"
#include<math.h>


class accTable : public BaseGuidance
{
public:
	accTable();

	~accTable();

	void initializeGuidance();

	void calcGuidance(Float64 FlightTime,
					  AerodynamicStruct &AeroData,
					  ThrustStruct &ThrustData,
					  AircraftStruct &AircraftData,
					  AirframeStruct &AirframeData,
					  AtmosphereStruct & AtmosphereData,
					  GuidanceStruct &GuidanceData);

private:
	Eigen::MatrixXd AccTable;
	Eigen::RowVectorXd s_x;
	Eigen::RowVectorXd s_y;
	Eigen::RowVectorXd s_z;
	Eigen::RowVectorXd v_x;
	Eigen::RowVectorXd v_y;
	Eigen::RowVectorXd v_z;
	Eigen::RowVectorXd a_x_com;
	Eigen::RowVectorXd a_y_com;
	Eigen::RowVectorXd a_z_com;

	Eigen::Vector3f Vec_fg;

};