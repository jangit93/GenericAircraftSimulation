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
#include"LinearInterpolation.h"
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
	//objects
	readInData *readIn;
	LinearInterpolation Interpolation;

	//Aircraft Data
	Float64 b;
	Float64 S;
	Float64 l_nu;
	
	//derivatives lift table
	Eigen::MatrixXd CA;
	Eigen::MatrixXd CAalpha;
	Eigen::MatrixXd CAeta;
	Eigen::MatrixXd CAq;

	//derivatives drag table
	Eigen::MatrixXd CW;
	Eigen::MatrixXd CWeta;

	//derivatives pitching moment table
	Eigen::MatrixXd CM;
	Eigen::MatrixXd CMalpha;
	Eigen::MatrixXd CMeta;
	Eigen::VectorXd CMq;

	//rolling moment table
	Eigen::MatrixXd CN;
	Eigen::MatrixXd CNp;
	Eigen::MatrixXd CNr;
	Eigen::MatrixXd CNxi;

	//yawing moment table
	Eigen::MatrixXd CL;
	Eigen::MatrixXd CLp;
	Eigen::MatrixXd CLq;
	Eigen::MatrixXd CLr;
	Eigen::MatrixXd CLxi;

	//vectors for interpolation 
	Eigen::VectorXd AoA;
	Eigen::VectorXd Mach;
	Eigen::VectorXd Xi;
	Eigen::VectorXd AoS;
	Eigen::VectorXd Eta;
	
	//derivatives
	Float64 c_a; 	
	Float64 c_aEta; 
    Float64 c_w; 
	Float64 c_weta;

    Float64 c_m; 	
    Float64 c_meta; 
    Float64 c_mq; 	
    Float64 c_A; 	
    Float64 c_aq; 	
    
    //Float64 CQ = 
    //Float64 CQy =
    
    Float64 c_l; 	
    Float64 c_lxi; 	
    Float64 c_lp; 	
    Float64 c_lr; 	
    //Float64 Clzet
    
    Float64 c_n; 	
    Float64 c_nxi; 	
    Float64 c_np; 	
    Float64 c_nr; 	
    Float64 c_nzeta;
	
	//Flight mechanical variables
	Float64 absVel ;			
	Float64 rho; 			
	Float64 SpeedOfSound; 	

    Float64 Ma;				
    Float64 qbar; 			
    
    Eigen::Vector3d  velBody;
	Eigen::Vector3d relVelNED;

    Float64 Alpha; 			
    Float64 Beta; 	
	Float64 ETA;
	Float64 XI;
	Float64 ZETA;
    
	Float64 alpha;
	Float64 beta;
    Float64 eta; 			
    Float64 xi; 				
    Float64 zeta; 			
    
    Float64 p; 				
    Float64 q; 				
    Float64 r; 	

	Float64 C_A;
	Float64 C_W;
	Float64 C_Q;
	Float64 C_L;
	Float64 C_M;
	Float64 C_N;
	Float64 C_X;
	Float64 C_Y;
	Float64 C_Z;
};
#endif DATCOMAERODYNAMIC_H	