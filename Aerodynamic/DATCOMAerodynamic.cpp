#include "DATCOMAerodynamic.h"

DATCOMAerodymamic::DATCOMAerodymamic()
{
	readIn = new readInData;
	
	logAeroData = new DataLogger("AerodynamicData.txt", 25, " ");
}

DATCOMAerodymamic::~DATCOMAerodymamic()
{
}

void DATCOMAerodymamic::initAerodynamic(Float64 &FlightTime, 
										AerodynamicStruct & AeroData,
										AircraftStruct & AircraftData)
{
	/// 1) read in tables of  aerdynamic derivatives
	MatFileReader readAeroData("../Input/ADM.mat");
	std::get<0>(readAeroData.readMatFileData("C_A"));
	readIn->setPath("../Input/Aerodynamics/");

	
	CA		= std::get<0>(readAeroData.readMatFileData("C_A"));
	CAeta	= std::get<0>(readAeroData.readMatFileData("C_Aeta"));
	CAq		= std::get<1>(readAeroData.readMatFileData("C_Aq"));
	CAalpha = std::get<0>(readAeroData.readMatFileData("C_Aalpha"));
			 
	CW		= std::get<0>(readAeroData.readMatFileData("C_W"));
	CWeta   = std::get<0>(readAeroData.readMatFileData("C_Weta"));
		
	CQ		= std::get<0>(readAeroData.readMatFileData("C_Y"));
	CQp		= std::get<0>(readAeroData.readMatFileData("C_Yp"));
	CQzeta	= std::get<2>(readAeroData.readMatFileData("C_Yzeta"));

	CM		= std::get<0>(readAeroData.readMatFileData("C_M"));
	CMalpha = std::get<0>(readAeroData.readMatFileData("C_Malpha"));
	CMeta	= std::get<0>(readAeroData.readMatFileData("C_Meta"));
	CMq		= std::get<1>(readAeroData.readMatFileData("C_Mq"));
			  
	CN		= std::get<0>(readAeroData.readMatFileData("C_N"));
	CNp		= std::get<0>(readAeroData.readMatFileData("C_Np"));
	CNr		= std::get<0>(readAeroData.readMatFileData("C_Nr"));
	CNxi	= std::get<0>(readAeroData.readMatFileData("C_Nxi"));
	CNzeta = std::get<2>(readAeroData.readMatFileData("C_Nzeta"));

	CL		= std::get<0>(readAeroData.readMatFileData("C_L"));
	CLp		= std::get<0>(readAeroData.readMatFileData("C_Lp"));
	CLr		= std::get<0>(readAeroData.readMatFileData("C_Lr")); 
	CLxi	= std::get<0>(readAeroData.readMatFileData("C_Lxi"));
	CLzeta = std::get<2>(readAeroData.readMatFileData("C_Lzeta"));


	AoA		= std::get<1>(readAeroData.readMatFileData("AoA"));
	AoS		= std::get<1>(readAeroData.readMatFileData("AoS"));
	Mach	= std::get<1>(readAeroData.readMatFileData("Mach"));
	Xi		= std::get<1>(readAeroData.readMatFileData("Xi"));
	Eta		= std::get<1>(readAeroData.readMatFileData("Eta"));

	b = AircraftData.wingspan;
	S = AircraftData.wingarea;
	l_nu = AircraftData.MAC;
	alpha0 = 0;

	initLogAeroData(FlightTime,AeroData);
}

void DATCOMAerodymamic::updateAerodynamic(Float64 FlightTime,
										AtmosphereStruct &AtmoData,
										AerodynamicStruct &AeroData,
										AirframeStruct &AirframeData,
										ThrustStruct &ThrustData, 
										ActuatorStruct &ActuatorData, 
										IMUStruct &IMUData, 
										NavigationStruct  &NavData)
{
	/// 1) get data from structures
	relVelNED = NavData.velNED;

	 AeroData.absVel    = sqrt(relVelNED(0)*relVelNED(0)+ relVelNED(1)*relVelNED(1)+ relVelNED(2)*relVelNED(2));
	 absVel			    = AeroData.absVel;
	 rho 				= AtmoData.rho;
	 SpeedOfSound 		= AtmoData.speedOfSound;

	 Ma					= absVel / SpeedOfSound;
	 qbar 				= 0.5*rho*absVel*absVel;


	 velBody				= AirframeData.matNEDToBody*relVelNED;
	 AirframeData.velBody	= velBody;
	
	 Alpha 	= atan2(velBody(2), velBody(0)) * 180 / PI;
	 Beta 	= atan2(velBody(1), sqrt(velBody(0)*velBody(0)+ velBody(1)*velBody(1)+ velBody(2)*velBody(2))) * 180 / PI;

	 ETA 	= ActuatorData.Eta * 180 / PI;
	 XI		= ActuatorData.Xi * 180 / PI;
	 ZETA	= ActuatorData.Zeta * 180 / PI;
	 
	 p = IMUData.rotRatesBody(0) * b / (2 * absVel);
	 q = IMUData.rotRatesBody(1) * l_nu/absVel;
	 r = IMUData.rotRatesBody(2)* b / (2 * absVel);


	if (Ma >= 0.9)
	{
		Ma = 0.9;
	}

	/// 2) depending on flight states interpolate derivatives
	c_a 	= Interpolation.linearInterpolation2D(AoA, Mach, CA, Alpha, Ma);
	c_aEta 	= Interpolation.linearInterpolation2D(Eta, Mach, CAeta, ETA, Ma);
	c_w 	= Interpolation.linearInterpolation2D(AoA, Mach, CW, Alpha, Ma);
	c_weta 	= Interpolation.linearInterpolation2D(Eta, Mach, CWeta, ETA, Ma);
	c_m 	= Interpolation.linearInterpolation2D(AoA, Mach, CM, Alpha, Ma);
	c_meta 	= Interpolation.linearInterpolation2D(Eta, Mach, CMeta, ETA, Ma);
	c_mq 	= Interpolation.linearInterpolation1D(Mach, CMq,Ma);
	c_aq 	= Interpolation.linearInterpolation1D(Mach, CAq, Ma);

	c_y     = Interpolation.linearInterpolation2D(AoS, Mach, CQ, Beta, Ma);
	c_yp    = Interpolation.linearInterpolation2D(AoA, Mach, CQp, Alpha, Ma);
	c_yzeta = CQzeta;
	c_yxi   = CQzeta;
	
	c_l 	= Interpolation.linearInterpolation2D(AoS, Mach, CL, Beta, Ma);
	c_lxi 	= Interpolation.linearInterpolation2D(Xi, Mach, CLxi, XI, Ma);
	c_lp 	= Interpolation.linearInterpolation2D(AoA, Mach, CLp, Alpha, Ma);
	c_lr 	= Interpolation.linearInterpolation2D(AoA, Mach, CLr, Alpha, Ma);
	c_lzeta = CLzeta;

	c_n 	= Interpolation.linearInterpolation2D(AoS, Mach, CN, Beta, Ma);
	c_nxi 	= Interpolation.linearInterpolation2D(Xi, Mach, CNxi, XI, Ma);
	c_np 	= Interpolation.linearInterpolation2D(AoA, Mach, CNp, Alpha, Ma);
	c_nr 	= Interpolation.linearInterpolation2D(AoA, Mach, CNr, Alpha, Ma);
	c_nzeta = CNzeta;
	
	alpha	= Alpha * PI / 180;
	beta	= Beta * PI / 180;
	eta		= ETA * PI / 180;
	xi		= XI * PI / 180;
	zeta	= ZETA * PI / 180;


	/// 3) calculate aerodynamic coefficients
	C_A = c_a + c_aq * q + c_aEta *eta;

	C_W = c_w + c_weta * eta;

	C_Q = c_y + c_yp*p   + c_yzeta*zeta + c_yxi*xi; 

	C_L = c_l + c_lp * p + c_lr * r + c_lxi * xi + c_lzeta * zeta; 

	C_M = c_m + c_mq * q + c_meta * eta;

	C_N = c_n + c_np * p + c_nr *r + c_nxi * xi  + c_nzeta*zeta;

	C_X = -C_W * cos(alpha) * cos(beta) - C_Q  *cos(alpha) * sin(beta) + C_A * sin(alpha);
	
	C_Y = C_Q * cos(beta) - C_W*sin(beta); 

	C_Z = -C_W * sin(alpha) * cos(beta) - C_Q  *sin(alpha) * sin(beta) - C_A * cos(alpha);

	/// 4) calculate derivatives for acceleration table guidance
	
	ca_alpha			= Interpolation.linearInterpolation2D(AoA, Mach, CAalpha, Alpha, Ma);
	AeroData.C_A0		= Interpolation.linearInterpolation2D(AoA, Mach, CA, alpha0, Ma);
	AeroData.C_zdalpha	= -C_W - ca_alpha;

	/// 5) store data to aerodynamic struct
	AeroData.AeroForces(0) = C_X * qbar*S;
	AeroData.AeroForces(1) = C_Y * qbar*S;
	AeroData.AeroForces(2) = C_Z * qbar*S;

	AeroData.AeroMoments(0) = C_L * qbar*S * (b / 2);
	AeroData.AeroMoments(1) = C_M * qbar*S *  l_nu;
	AeroData.AeroMoments(2) = C_N * qbar*S * (b / 2);


	AeroData.CA = C_A;
	AeroData.CW = C_W;
	AeroData.CM = C_M;
	AeroData.CZ = C_Z;
	AeroData.CX = C_X;
	AeroData.Alpha = alpha;
	AeroData.AoA   = alpha;
	AeroData.Beta  = beta;
	AeroData.Mach  = Ma;
	AeroData.q_bar = qbar;


}

void DATCOMAerodymamic::initLogAeroData(Float64 &FlightTime,
										AerodynamicStruct & AeroData)
{
	
	logAeroData->add("Time [s]", FlightTime);
	logAeroData->add("AoA", AeroData.Alpha);
	logAeroData->add("AoS", AeroData.Beta);
	logAeroData->add("CA", AeroData.CA);
	logAeroData->add("CM", AeroData.CM);
	logAeroData->add("CW", AeroData.CW);
	logAeroData->add("F_x", AeroData.AeroForces(0));
	logAeroData->add("F_y", AeroData.AeroForces(1));
	logAeroData->add("F_z", AeroData.AeroForces(2));

	logAeroData->printHeader();
}

void DATCOMAerodymamic::LogAeroData()
{
	logAeroData->print();
}

