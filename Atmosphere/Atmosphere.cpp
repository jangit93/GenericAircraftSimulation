#include "Atmosphere.h"

Atmopshere::Atmopshere()
{
}

Atmopshere::~Atmopshere()
{
}

void Atmopshere::initAtmosphere()
{

	std::cout << "Atmosphere: " << "Standard Atmosphere 1967" << std::endl;

	Temperature		= 0.0;	
	Pressure		= 0.0;       
	rho				= 0.0;			
	speedOfSound	= 0.0;   
}

void Atmopshere::updateAtmosphere(Float64 &Altitude, 
								  AtmosphereStruct &AtmoData)
{

	///troposphere
	if (Altitude < 11000.0)
	{
		Temperature = 15.04 - 0.00649 * Altitude + 273.1;
		Pressure = 101.29 * pow(Temperature / 288.08,5.256);
	}

	/// lower stratosphere	
	else if(Altitude < 25000.0)
	{
				Temperature = -56.46 + 273.1;
				Pressure = 22.65 * exp(1.73 - 0.000157 * Altitude);
	}


	///upper stratosphere--> Altitude >= 25000.0
	else
	{ 
			Temperature = -131.21 + 0.00299 * Altitude + 273.1;
			Pressure = 2.488 * pow(Temperature / 216.6,-11.388);
	}
		

			rho			 = Pressure / (0.2869 * Temperature);           
			speedOfSound = sqrt(GAMMA * GAS_CONSTANT * Temperature);
			Pressure	 = Pressure * 1000;

			AtmoData.rho = rho;
			AtmoData.Pressure = Pressure;
			AtmoData.speedOfSound = speedOfSound;
			AtmoData.Temperature = Temperature;
}
