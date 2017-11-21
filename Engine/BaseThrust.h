#ifndef BaseThrust_H
#define BaseThrust_H

#include<math.h>
#include"DataCloud.h"
#include"readInData.h"
#include"IndependetDataTypes.h"
#include"../EIGENDIR/Eigen/Dense"


class BaseThrust {

public:
	BaseThrust();

	~BaseThrust();

	void updateThrust(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

	void initThrust();

	virtual void calcThrust(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

	virtual void initializeThrust();

};

#endif	BaseThrust_H