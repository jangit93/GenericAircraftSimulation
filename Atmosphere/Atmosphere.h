//////////////////////////////////////////////////////////////////////////////////////////
//
// class name:			Atmosphere
//
// short description:	class which calculates atmosphere parameter (NASA 1987)
//
// Date:				22.10.2017
//
// Author:				Jan Olucak
//
// external sources:	-Bachelorarbeit Jan Olucak
//
// revision:			1.0
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef ATMOSPHERE__HPP
#define ATMOSPHERE__HPP

#include <math.h>
#include <iostream>
#include"../Tools/Constants.h"
#include"../DataCloud/DataCloud.h"

typedef double Float64;

class Atmopshere
{
public:

	Atmopshere();

	~Atmopshere();

	void	initAtmosphere();

	void	updateAtmosphere(Float64 &Altitude, AtmosphereStruct &AtmoData);

private:
	Float64	Temperature;	// [K]
	Float64 Pressure;       //[Pa]
	Float64	rho;			//[Kg / m³]
	Float64 speedOfSound;   //[m / s]
	
	AtmosphereStruct AtmosphereData;

};

#endif	ATMOSPHERE__HPP
