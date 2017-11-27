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
#include"../EIGENDIR/Eigen/Dense"

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
*
*/
struct AerodynamicStruct
{
	Float64 AoA;		
	Float64 AoS;
	Float64 VelAero;	
	Eigen::Vector3d AeroForces;
	Eigen::Vector3d AeroMoments;
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
* @param intertiaTensor
* @param accTransBody	vector of translational acceleration body fixed coordinate system
* @param accRotBody		vector of rotational acceleration body fixed coordinate system
* @param EulerAngles	vector of euler angles
* @param velBody		vector of velocity in body fixed coordinate system
* @param rotRatesBody	vecotr of body fixed rotational rates
* @param Eulerdot		vecotr of derivatives of euler angles
*/
struct AirframeStruct {
	Float64 StickPosition;	
	Eigen::Matrix3d intertiaTensor;
	Eigen::Vector3d accTransBody;
	Eigen::Vector3d accRotBody;
	Eigen::Vector3d EulerAngles;
	Eigen::Vector3d velBody;
	Eigen::Vector3d rotRatesBody;
	Eigen::Vector3d Eulerdot;

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
/**@}*/
#endif	DATACLOUD_H