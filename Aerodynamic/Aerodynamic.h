/** @defgroup	Aerodynamic Aerodynamic
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Aerodynamic class is used to call the desired aerodynamic model. The engine model is selected from
*	General.dat input file.
*  @{
*/

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

	/**
	* \brief constructor
	*/
	Aerodynamics();

	/**
	* \brief destructor
	*/
	~Aerodynamics();

	/**
	* \brief set pointer to desired class
	*/
	void selectAerodynamicType(int type);

	/**
	* \brief initialize aerodynamic paramters
	*/
	void initAerodynamic(AerodynamicStruct & AeroData, 
						 AircraftStruct & AircraftDatas);

	/**
	* \brief calculate aero forces and moments
	*/
	void updateAerodynamic(Float64 FlightTime,
							AtmosphereStruct & AtmoData,
							AerodynamicStruct & AeroData,
							AirframeStruct & AirframeData,
							ThrustStruct & ThrustData);

private:
	BaseAerodynamic * aerodynamic;
};
/**@}*/
#endif	AERODYNAMIC_H