#include "DATCOMAerodynamic.h"

DATCOMAerodymamic::DATCOMAerodymamic()
{
	readIn = new readInData;
}

DATCOMAerodymamic::~DATCOMAerodymamic()
{
}

void DATCOMAerodymamic::initAerodynamic(AerodynamicStruct & AeroData,
											  AircraftStruct & AircraftData)
{

	MatFileReader readAeroData("../ADM.mat");
	std::get<0>(readAeroData.readMatFileData("C_A"));
	readIn->setPath("../Input/Aerodynamics/");

	//read in tables of derivatives
	CA		= std::get<0>(readAeroData.readMatFileData("C_A"));//readIn->readInTable("CL.txt");
	CAeta	= std::get<0>(readAeroData.readMatFileData("C_Aeta"));//readIn->readInTable("CLeta.txt");
	CAq		= std::get<1>(readAeroData.readMatFileData("C_Aq"));//readIn->readInVector("CLQ.txt");
	CAalpha = std::get<0>(readAeroData.readMatFileData("C_Aalpha"));
			 
	CW		= std::get<0>(readAeroData.readMatFileData("C_W"));//readIn->readInTable("CD.txt");
	CWeta   = std::get<0>(readAeroData.readMatFileData("C_Weta"));//readIn->readInTable("CDeta.txt");
		
	CQ		= std::get<0>(readAeroData.readMatFileData("C_Y"));
	CQp		= std::get<0>(readAeroData.readMatFileData("C_Yp"));
	CQzeta	= std::get<2>(readAeroData.readMatFileData("C_Yzeta"));

	CM		= std::get<0>(readAeroData.readMatFileData("C_M"));//readIn->readInTable("CM.txt");
	CMalpha = std::get<0>(readAeroData.readMatFileData("C_Malpha"));//readIn->readInTable("CMA.txt");
	CMeta	= std::get<0>(readAeroData.readMatFileData("C_Meta"));//readIn->readInTable("CMeta.txt");
	CMq		= std::get<1>(readAeroData.readMatFileData("C_Mq"));//readIn->readInVector("CMq.txt");
			  
	CN		= std::get<0>(readAeroData.readMatFileData("C_N"));//readIn->readInTable("CN.txt");
	CNp		= std::get<0>(readAeroData.readMatFileData("C_Np"));//readIn->readInTable("CNP.txt");
	CNr		= std::get<0>(readAeroData.readMatFileData("C_Nr"));//readIn->readInTable("CNR.txt");
	CNxi	= std::get<0>(readAeroData.readMatFileData("C_Nxi"));//readIn->readInTable("CNxi.txt");
	CNzeta = std::get<2>(readAeroData.readMatFileData("C_Nzeta"));

	CL		= std::get<0>(readAeroData.readMatFileData("C_L"));//readIn->readInTable("CLmoment.txt");
	CLp		= std::get<0>(readAeroData.readMatFileData("C_Lp"));//readIn->readInTable("CLP.txt");
	CLr		= std::get<0>(readAeroData.readMatFileData("C_Lr")); //readIn->readInTable("CLR.txt");
	CLxi	= std::get<0>(readAeroData.readMatFileData("C_Lxi"));//readIn->readInTable("CLxi.txt");
	CLzeta = std::get<2>(readAeroData.readMatFileData("C_Lzeta"));

	//read in Vectors for interpolation
	AoA		= std::get<1>(readAeroData.readMatFileData("AoA"));//readIn->readInVector("AoA.txt");
	AoS		= std::get<1>(readAeroData.readMatFileData("AoS"));//readIn->readInVector("AoS.txt");
	Mach	= std::get<1>(readAeroData.readMatFileData("Mach"));//readIn->readInVector("Ma.txt");
	Xi		= std::get<1>(readAeroData.readMatFileData("Xi"));//readIn->readInVector("Xi.txt");
	Eta		= std::get<1>(readAeroData.readMatFileData("Eta"));//readIn->readInVector("Eta.txt");

	b = AircraftData.wingspan;
	S = AircraftData.wingarea;
	l_nu = AircraftData.MAC;

}

void DATCOMAerodymamic::updateAerodynamic(Float64 FlightTime,
										AtmosphereStruct & AtmoData,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData)
{
	relVelNED = AirframeData.velNED;

	 absVel 			= sqrt(relVelNED(0)*relVelNED(0)+ relVelNED(1)*relVelNED(1)+ relVelNED(2)*relVelNED(2));
	 rho 				= AtmoData.rho;
	 SpeedOfSound 		= AtmoData.speedOfSound;

	 Ma					= absVel / SpeedOfSound;
	 qbar 				= 0.5*rho*absVel*absVel;


	velBody 				= AirframeData.matNEDToBody*AirframeData.velNED;
	AirframeData.velBody	= velBody;
	
	 Alpha 	= atan2(velBody(2), velBody(0)) * 180 / PI;
	 Beta 	= atan2(velBody(1), sqrt(velBody(0)*velBody(0)+ velBody(1)*velBody(1)+ velBody(2)*velBody(2))) * 180 / PI;

	 ETA 	= AirframeData.Eta * 180 / PI;
	 XI		= AirframeData.Xi * 180 / PI;
	 ZETA	= AirframeData.Zeta * 180 / PI;
	 
	 p = AirframeData.rotRatesBody(0) * b / 2 * absVel;
	 q = AirframeData.rotRatesBody(1) * l_nu*absVel;
	 r = AirframeData.rotRatesBody(2)* b / 2 * absVel;


	if (Ma >= 0.9)
	{
		Ma = 0.9;
	}

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

	C_A = c_a + c_aq * q + c_aEta *eta;

	C_W = c_w + c_weta * eta;

	C_Q = c_y + c_yp*p   + c_yzeta*zeta + c_yxi*xi;  //Fehler in Aeromodell BA!!!!!

	C_L = c_l + c_lp * p + c_lr * r + c_lxi * xi + c_lzeta * zeta; 

	C_M = c_m + c_mq * q + c_meta * eta;

	C_N = c_n + c_np * p + c_nr *r + c_nxi * xi  + c_nzeta*zeta;

	C_X = -C_W * cos(alpha) * cos(beta) - C_Q  *cos(alpha) * sin(beta) + C_A * sin(alpha);
	
	C_Y = C_Q * cos(beta) - C_W*sin(beta); 

	C_Z = -C_W * sin(alpha) * cos(beta) - C_Q  *sin(alpha) * sin(beta) - C_A * cos(alpha);

	// Guidanc daten noch ergänzen
	ca_alpha = Interpolation.linearInterpolation2D(AoA, Mach, CAalpha, Alpha, Ma);
	ca_0 = Interpolation.linearInterpolation2D(AoA, Mach, CA, 0, Ma);
	c_zdalpha = -C_W - ca_alpha;

	// Kräfte und Momente
	AeroData.AeroForces(0) = C_X * qbar*S;
	AeroData.AeroForces(1) = C_Y * qbar*S;
	AeroData.AeroForces(2) = C_Z * qbar*S;

	AeroData.AeroMoments(0) = C_L * qbar*S * (b / 2);
	AeroData.AeroMoments(1) = C_M * qbar*S *  l_nu;
	AeroData.AeroMoments(2) = C_N * qbar*S * (b / 2);
	
	// Daten in Struktur
	AeroData.C_zdalpha = c_zdalpha;
	AeroData.C_A0 = ca_0;

	AeroData.CA = C_A;
	AeroData.CW = C_W;
	AeroData.CM = C_M;
	AeroData.CZ = C_Z;
	AeroData.CX = C_X;
	AeroData.AoA = Alpha;
	AeroData.AoS = Beta;
	AeroData.Mach = Ma;


}
