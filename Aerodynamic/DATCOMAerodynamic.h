/**
*	@ingroup Aerodynamic
*	@author Jan Olucak
*	@date 25.11.2017
*	@version 1.0
*
*	DATCOm aerodynamic class is a child class from BaseAerodynamic. This class
*	calculates aerodynamic forces and moments with tables from DATCOM. Tables of
*	derivative are read in from specific file.
*
*/

#include"Constants.h"
#include"BaseAerodynamic.h"
#include"readInData.h"
#include<math.h>

#ifndef DATCOMAERODYNAMIC_H
#define DATCOMAERODYNAMIC_H

class DATCOMAerodymamic : public BaseAerodynamic
{
public:
	/**
	* @brief constructor
	*/
	DATCOMAerodymamic();

	/**
	* @brief destructor
	*/
	~DATCOMAerodymamic();

	/**
	* @brief read in tables of derivatives
	*/
	void initializeAerodynamic(AerodynamicStruct & AeroData, 
							   AircraftStruct & AircraftData);

	/**
	* @brief	current flight state is used to interpolated derivatives
				and  a linear aerodynamic model calculates forces
				and moments
	*/
	void calcAerodynamic(Float64 FlightTime,
						AtmosphereStruct & AtmoData,
						AerodynamicStruct & AeroData,
						AirframeStruct & AirframeData,
						ThrustStruct & ThrustData);

private:
	readInData *readIn;

	//derivatives lift
	Eigen::MatrixXd CA;
	Eigen::MatrixXd CAalpha;
	Eigen::MatrixXd CAeta;
	Eigen::MatrixXd CAq;

	//derivatives drag
	Eigen::MatrixXd CW;
	Eigen::MatrixXd CWeta;

	//derivatives pitching moment
	Eigen::MatrixXd CM;
	Eigen::MatrixXd CMalpha;
	Eigen::MatrixXd CMeta;
	Eigen::VectorXd CMq;

	//rolling moment
	Eigen::MatrixXd CN;
	Eigen::MatrixXd CNp;
	Eigen::MatrixXd CNr;
	Eigen::MatrixXd CNxi;

	//yawing moment
	Eigen::MatrixXd CL;
	Eigen::MatrixXd CLp;
	Eigen::MatrixXd CLq;
	Eigen::MatrixXd CLr;
	Eigen::MatrixXd CLxi;

	//vectors for interpolation
	Eigen::VectorXd AoA;
	Eigen::VectorXd Ma;
	Eigen::VectorXd Xi;
	Eigen::VectorXd AoS;
};

#endif DATCOMAERODYNAMIC_H
