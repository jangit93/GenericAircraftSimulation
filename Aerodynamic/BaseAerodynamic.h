#ifndef BASEAERODYNAMIC_H
#define BASEAERODYNAMIC_H

#include<math.h>
#include<iostream>
#include"DataCloud.h"
#include"IndependetDataTypes.h"
#include"../EIGENDIR/Eigen/Dense"

class BaseAerodynamic {

public:
	BaseAerodynamic();

	~BaseAerodynamic();

	void updateAerodynamic(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

	void initAerodynamic();

	virtual void calcAerodynamic(Float64 FlightTime,
								AtmosphereStruct & AtmoData,
								AerodynamicStruct & AeroData,
								AirframeStruct & AirframeData,
								ThrustStruct & ThrustData);

	virtual void initializeAerodynamic();

};
#endif BASEAERODYNAMIC