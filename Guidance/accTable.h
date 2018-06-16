/**
*	@ingroup Guidance
*	@author Jan Olucak
*	@date 23.12.2017
*	@version 1.0
*
*	accTable class is a child class from BaseGuidance. This class
*	calculates calculates commands for the autopilot. Tables of
*	acceleration and velocity are read in as a function of time. 
*	Depending on accelerations commands for the state controller 
*	are calculated
*
*/

#ifndef ACCTABLE_H
#define ACCTABLE_H

#include<iostream>
#include"DataCloud.h"
#include"IndependetDataTypes.h"
#include"BaseGuidance.h"
#include"MatFileReader.h"
#include"Constants.h"
#include<math.h>
#include"Transformation.h"
#include"DataLogger.h"

class accTable : public BaseGuidance
{
public:
	/**
	* \brief constructor
	*/
	accTable();

	/**
	* \brief destructor
	*/
	~accTable();

	/**
	* \brief accTables are read in and stored in row vectors
	*	@param	FlightTime			flight time
	*	@param	GuidanceData		structure of Guidance data
	*	@param	AircraftData		specific airfraft data
	*/
	void initGuidance(Float64 &FlightTime, 
					  GuidanceStruct &GuidanceData, 
					  AircraftStruct &AircraftData);
	/**
	* \brief calculate commands for flight path
	*	@param	FlightTime			flight time
	*	@param	AeroData			structure of aero data
	*	@param	ThrustData			structure of thrust data
	*	@param	AirframeData		structure of airframe data
	*	@param	GuidanceData		structure of guidance data
	*/
	void updateGuidance(Float64 FlightTime,
					    AerodynamicStruct &AeroData,
					    ThrustStruct &ThrustData,
					    AirframeStruct &AirframeData,
					    GuidanceStruct &GuidanceData);

	/**
	* \brief desired data for logging are selected
	*	@param	FlightTime			flight time
	*	@param	GuidanceData		structure of guidance data
	*/
	virtual void initLogGuidance(Float64 &FlightTime, 
								 GuidanceStruct &GuidanceData);

	/**
	* \brief  logging of guidance data
	*/
	virtual void logGuidanceData();

private:

	//obejcts
	DataLogger *LogGuidanceData;

	//variables
	Float64 flightTime;
	int reshape;
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

	Eigen::Vector3d accNED;
	Eigen::Vector3d velNED;
	Eigen::Vector3d accBody;
	Eigen::Vector3d velBody;
	Eigen::Vector3d accTraj;

	Float64 Alpha_com;
	Float64 Beta_com;
	Float64 chi_dot;

	Float64 mass;
	Float64 wingarea;

	// help function
	Float64	G;
	Float64 a;
	Float64 b;
	Float64 c;
	Float64 a1;
	Float64 b1;
};
#endif ACCTABLE_H