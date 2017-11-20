#ifndef DATACLOUD_H
#define DATACLOUD_H

#include"../Tools/IndependetDataTypes.h"
#include"../EIGENDIR/Eigen/Dense"

struct AtmosphereStruct
{
	Float64	Temperature;	// [K]
	Float64 Pressure;       //[Pa]
	Float64	rho;			//[Kg / m³]
	Float64 speedOfSound;   //[m / s]
};

struct AerodynamicStruct
{
	Float64 AoA;
	Float64 VelAero;
};

struct ThrustStruct {
	Eigen::Vector3d ThrustForce;
	Eigen::Vector3d	ThrustMoments;
	Float64	F_max;   //maximum Thrust[N]
	Float64	i;       //engine installation angle[rad]
	Float64 r;       //enginge position vector[m, m, m]
	Float64	Kt;      //engine constant[-]
};

struct AirframeStruct {
	Float64 StickPosition;
};

#endif	DATACLOUD_H