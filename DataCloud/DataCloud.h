#ifndef DATACLOUD_H
#define DATACLOUD_H

typedef double Float64;

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
};

struct ThrustStruct {
	Float64 i;
};

#endif	DATACLOUD_H