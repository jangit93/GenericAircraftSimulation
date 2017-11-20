#include"BaseThrust.h"
#include"Constants.h"
#include<math.h>

#ifndef THRUSTANALYTICAL_H
#define THRUSTANALYTICAL_H

class ThrustAnalytical : public BaseThrust {
public:
	ThrustAnalytical();

	~ThrustAnalytical();

	void initThrust();

	void updateThrust(Float64 FlightTime,
					  AtmosphereStruct &AtmoData, 
					  AerodynamicStruct &AeroData,
					  AirframeStruct &AirframeData,
					  ThrustStruct &ThrustData);

private:
	Eigen::Vector3d ThrustForce;
	Eigen::Vector3d ThrustMoment;
	Float64 rho;
	Float64 Mach;
	Float64 StickPosition;
	Float64 absThrust;
	int maxThrust;
	Float64 Kt;
	Float64 incidenceAngle;
	Eigen::Vector3d EnginePos;

};
#endif // !THRUSTANALYTICAL_H
