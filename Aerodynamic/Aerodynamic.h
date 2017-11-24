#ifndef AERODYNAMIC_H
#define AERODYNAMIC_H

#include<math.h>
#include"DataCloud.h"
#include"readInData.h"
#include"IndependetDataTypes.h"
#include"../EIGENDIR/Eigen/Dense"
#include"BaseAerodynamic.h"
#include"DATCOMAerodynamic.h"


class Aerodynamics {

public:
	Aerodynamics();

	~Aerodynamics();

	void selectAerodynamicType(int type);

	void initAerodynamic();

	void updateAerodynamic(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

private:
	BaseAerodynamic * aerodynamic;
};

#endif	AERODYNAMIC_H