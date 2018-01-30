/** @defgroup	DataCloud  DataCloud
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	DataCloud is a global data storage for structures. It serves the purpose to provide data 
*	for several applications like the simulation itself, module and unit tests. 
*  @{
*/
#ifndef DATACLOUD_H
#define DATACLOUD_H

#include"../Tools/IndependetDataTypes.h"
#include<Eigen/Dense>

/** 
* \brief stores atmospheric data
* @param Temperatur		Altitude specific Temperature [K]
* @param Presure		Altitude specific Pressure [Pa]
* @param rho			Altitude specific air density [\f$\frac{Kg}{m^3}$]
* @param speedOfSound	Altitude specific speed of sound [m/s]
*/
struct AtmosphereStruct
{
	Float64	Temperature;	
	Float64 Pressure;       
	Float64	rho;			
	Float64 speedOfSound;   
};

/**
* \brief stores Aerodynamic data
* @ingroup	DataCloud
* @param  AoA			Angle of Attack
* @param  VelAero		Velocity in Aerodynamic coordinate system
* @param  AeroForces	Vector of all Aerodynamic forces
* @param  AeroMoments	Vector of all Aerodynamic Moments
* @param  AoS			Angle of Sidesip
* @param  Mach			Mach number
* @param  CA			lift coefficient
* @param  CW			drag coefficient
* @param  CM			pitching-moment coefficient
* @param  CX			body fixed coefficient x-direction
* @param  CZ			body fixed coefficient z-direction
* @param  C_A0			zero lift coefficient
* @param  C_zdalpha		derivative of body fixed coefficient in z-direction
* @param  q_bar			dynamic pressure
*/
struct AerodynamicStruct
{
	Float64 AoA;		
	Float64 AoS;
	Float64 VelAero;
	Float64 Mach;
	Float64 CA;
	Float64 CM;
	Float64 CW;
	Float64 CZ;
	Float64 CX;

	//data needed for guidance
	Float64 C_A0;
	Float64 C_zdalpha;

	Eigen::Vector3d AeroForces;
	Eigen::Vector3d AeroMoments;

	Float64 q_bar;
};

/**
* \brief stores thrust data
* @param ThrustForce	Vector of calculated thrust forces
* @param ThrustMoments	Vector of calculated thrust moments
* @param i				engine incidence angle 
* @param F_max			maximum thrust from input file
* @param r				Vector of engine position related to Center of Gravity
* @param Kt				engine specific constant from input file
*/
struct ThrustStruct {
	Eigen::Vector3d ThrustForce;	
	Eigen::Vector3d	ThrustMoments;	
	Float64	F_max;					
	Float64	i;						
	Eigen::Vector3d r;
	Float64	Kt;						
};

/**
* \brief stores Airframe data
* @param StickPosition	position of throttle
* @param intertiaTensor intertia Tensor
* @param accTransBody	vector of translational acceleration body fixed coordinate system
* @param accRotBody		vector of rotational acceleration body fixed coordinate system
* @param EulerAngles	vector of euler angles
* @param velBody		vector of velocity in body fixed coordinate system
* @param rotRatesBody	vecotr of body fixed rotational rates
* @param Eulerdot		vecotr of derivatives of euler angles
* @param velNED			velocity in North-East-Down coordinate system
* @param matNEDToTraj	transformation matrix NED to trajectory system
* @param matNEDToBody	transformation matrix NED to body system
* @param matBodyToNED	transformation matrix Body to NED system
*/
struct AirframeStruct {
	Float64 StickPosition;	
	Float64 Eta;
	Float64 Xi;
	Float64 Zeta;
	Eigen::Matrix3d intertiaTensor;
	Eigen::Vector3d accTransBody;
	Eigen::Vector3d accRotBody;
	Eigen::Vector3d EulerAngles;
	Eigen::Vector3d velBody;
	Eigen::Vector3d rotRatesBody;
	Eigen::Vector3d Eulerdot;
	Eigen::Vector3d velNED;
	Eigen::Matrix3d matNEDToTraj;
	Eigen::Matrix3d matNEDToBody;
	Eigen::Matrix3d matBodyToNED;

};

/**
* \brief stores Aircraft data
* @param mass Aircraft mass
* @param I_x moment of inertia[kg*m^2]
* @param I_y moment of inertia[kg*m^2]
* @param I_z moment of inertia[kg*m^2]
* @param I_zx moment of inertia[kg*m^2]
* @param wingarea 
* @param wingspan
* @param MAC Mean Aerodynamic Chord
* @param X_CG x position center of gravity
* @param Y_CG y position center of gravity
* @param Z_CG z position center of gravity
*/
struct AircraftStruct {
	Float64  mass;
	Float64  I_x;
	Float64	 I_y;
	Float64  I_z;
	Float64  I_zx;
	Float64  wingarea;
	Float64  wingspan;
	Float64  MAC;
	Float64  X_CG;
	Float64  Y_CG;
	Float64  Z_CG;
};
/**
* \brief stores parameters for gain scheduling
* @param Alt	Altitude of operating point
* @param Vel	Velocity of operating point
* @param u_bar	control vector of operating point
* @param x_bar 	state vector of operating point
* @param Kx_pitch 	control parameters for longitudinal movement
* @param Ke_pitch 	control parameters for longitudinal movement
* @param Kv_pitch 	control parameters for longitudinal movement
* @param Kx_Vel 	control parameters for longitudinal movement
* @param Ke_Vel 	control parameters for longitudinal movement
* @param Kx_lat 	control parameters for lateral movement
*/
struct AutopilotStruct {
	Float64 Alt;
	Float64 Vel;
	Eigen::VectorXd u_bar;
	Eigen::VectorXd x_bar;
	Eigen::VectorXd Kx_pitch;
	Float64 Ke_pitch;
	Float64 Kv_pitch;
	Float64 Kx_Vel;
	Float64 Ke_Vel;
	Eigen::MatrixXd Kx_lat;
};

/**
* \brief stores guidance parameters 
* @param Velocity_com	commanded velocity
* @param Theta_com		commanded pitch angle
* @param Phi_com		commanded roll angle
* @param Beta_com		command angle of sideslip
*/
struct GuidanceStruct
{
	Float64 Velocity_com;
	Float64	Theta_com;
	Float64 Phi_com;
    Float64 Beta_com;
};

struct IMUStruct
{
	Eigen::Vector3d realTransAcc;
	Eigen::Vector3d realTRotAcc;
};

struct NavigationStruct
{
	Eigen::Vector3d intVelocity;
	Eigen::Vector3d intPOS;
	Eigen::Vector3d realVelocity;
	Eigen::Vector3d realPOS;
};

/**@}*/	
#endif	DATACLOUD_H