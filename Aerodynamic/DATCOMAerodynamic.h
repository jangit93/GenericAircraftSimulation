#include"Constants.h"
#include"BaseAerodynamic.h"
#include<math.h>

#ifndef DATCOMAERODYNAMIC_H
#define DATCOMAERODYNAMIC_H

class DATCOMAerodymamic : public BaseAerodynamic
{
public:
	DATCOMAerodymamic();

	~DATCOMAerodymamic();

	void initializeAerodynamic();

	void calcAerodynamic(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

private:


};

#endif DATCOMAERODYNAMIC_H
