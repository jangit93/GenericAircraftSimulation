#ifndef DATACLOUD_HPP
#define DATACLOUD_HPP

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

#endif	DATACLOUD_HPP