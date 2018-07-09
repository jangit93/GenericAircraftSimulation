/**
*	@ingroup Autopilot
*	@author Jan Olucak
*	@date 10.04.2018
*	@version 1.0
*
*	StateController class simulates a state controller for flight states. Control variables are
*   calculated with blending method.
*
*/
#include"MatFileReader.h"
#include"DataCloud.h"
#include"FindNeighbor.h"

#include"Constants.h"

#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H


class StateController
{

public:
	/**
	* \brief construtor
	*/
	StateController();

	/**
	* \brief destrutor
	*/
	~StateController();

	/**
	* \brief read in and initalize state controller parameters 
	*/
	void initStateController();

	/**
	* \brief calculate controlls depending on flight state
	* @param	FlightTime		flight time
	* @param	AirframeData	flight states
	* @param	AeroData		get angle of attack
	* @param	GuidanceData	control input
	* @param	ActuatorData	actuator angles
	* @param	IMUData			rotatory rates
	* @param	NavData			velocity 
	*/
	void updateStateController(Float64 FlightTime,
								AirframeStruct &AirframeData,
								AerodynamicStruct &AeroData,
								GuidanceStruct &GuidanceData, 
								ActuatorStruct &ActuatorData, 
								IMUStruct &IMUData, 
								NavigationStruct &NavData);

	/**
	* \brief help functions to find index
	* @param	row		desired row
	* @param	column	desired column
	* @param	rows	total number of rows
	* @param	columns	total number of columns
	*/
	int sub2ind(const int row, 
				const int column,		
				const int rows, 
				const int columns);
	
	/**
	* \brief signum function
	*/
	int sign(Float64 val);

private:
	FindNeighbor * findneighbor;
	Eigen::Vector4d PHI;
	Eigen::MatrixXd NEIGHBOR;

	// parameters of matFileReader
	AutopilotStruct * StateControllertData;
	matvar_t MatFileData;
	MatFileReader *readAutopilotData;
	int Fields;
	int start;
	int stride;
	int edge;
	int copy_field;

	Float64 dt;
	int index;
	//trim point and controller
	Eigen::VectorXd x_0;
	Eigen::VectorXd u_0;
	Eigen::MatrixXd K_lat;
	Eigen::RowVector4d K_long_pitch;
	Float64 K_v;
	Eigen::RowVectorXd K_long_vel;
	Float64 e1_long;
	Float64 e2_long;

	//guidance
	Float64 theta_com;
	Float64 Vel_com;
	Float64 beta_com;
	Float64 phi_com;

	//states
	Eigen::VectorXd x_long_pitch;
	Eigen::VectorXd x_0_pitch;
	Eigen::VectorXd delta_x_long;
	Float64 delta_x_vel;
	Eigen::VectorXd x_lat;
	Eigen::VectorXd x_0_lat;
	Eigen::VectorXd delta_x_lat;
	Float64 e1_lat;
	Float64 e2_lat;
	Eigen::VectorXd e_lat;

	//controls
	Float64 delta_u_long;
	Eigen::Vector2d delta_u_lat;
	Float64 delta_u_vel;

	//gain scheduling
	Eigen::RowVector4d u_sched_eta;
	Eigen::RowVector4d u_sched_zeta;
	Eigen::RowVector4d u_sched_xi;
	Eigen::RowVector4d u_sched_delta;

	Eigen::Vector4d Delta_x_long;
	Eigen::Vector2d Delta_x_vel;
	Eigen::VectorXd	Delta_x_lat;
};
#endif