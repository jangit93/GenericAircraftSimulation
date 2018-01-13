#include "DATCOMAerodynamic.h"

DATCOMAerodymamic::DATCOMAerodymamic()
{
	readIn = new readInData;
}

DATCOMAerodymamic::~DATCOMAerodymamic()
{
}

void DATCOMAerodymamic::initializeAerodynamic(AerodynamicStruct & AeroData,
											  AircraftStruct & AircraftData)
{
	readIn->setPath("../Input/Aerodynamics/");

	//read in tables of derivatives
	CA		= readIn->readInTable("CL.txt");
	CAeta	= readIn->readInTable("CLeta.txt");
	CAq		= readIn->readInVector("CLQ.txt");

	CW		= readIn->readInTable("CD.txt");
	CWeta	= readIn->readInTable("CDeta.txt");

	CM		= readIn->readInTable("CM.txt");
	CMalpha = readIn->readInTable("CMA.txt");
	CMeta	= readIn->readInTable("CMeta.txt");
	CMq		= readIn->readInVector("CMq.txt");

	CN		= readIn->readInTable("CN.txt");
	CNp		= readIn->readInTable("CNP.txt");
	CNr		= readIn->readInTable("CNR.txt");
	CNxi	= readIn->readInTable("CNxi.txt");

	CL		= readIn->readInTable("CLmoment.txt");
	CLp		= readIn->readInTable("CLP.txt");
	CLr		= readIn->readInTable("CLR.txt");
	CLxi	= readIn->readInTable("CLxi.txt");

	//read in Vectors for interpolation
	AoA = readIn->readInVector("AoA.txt");
	AoS = readIn->readInVector("AoS.txt");
	Mach = readIn->readInVector("Ma.txt");
	Xi = readIn->readInVector("Xi.txt");
	Eta = readIn->readInVector("Eta.txt");

	b = AircraftData.wingspan;
	S = AircraftData.wingarea;
	l_nu = AircraftData.MAC;

}

void DATCOMAerodymamic::calcAerodynamic(Float64 FlightTime,
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

	//CQ = Interpolation.linearInterpolation2D(AoA, Mach, CL, Alpha, Ma);
	//CQy = Interpolation.linearInterpolation2D(AoA, Mach, CL, Alpha, Ma);
	/*
	c_l 	= Interpolation.linearInterpolation2D(AoA, Mach, CL, Alpha, Ma);
	c_lxi 	= Interpolation.linearInterpolation2D(AoA, Mach, CLxi, Alpha, Ma);
	c_lp 	= Interpolation.linearInterpolation2D(AoA, Mach, CLp, Alpha, Ma);
	c_lr 	= Interpolation.linearInterpolation2D(AoA, Mach, CLr, Alpha, Ma);
	//Clzeta = Clzeta;

	c_n 	= Interpolation.linearInterpolation2D(AoA, Mach, CN, Alpha, Ma);
	c_nxi 	= Interpolation.linearInterpolation2D(AoA, Mach, CNxi, Alpha, Ma);
	c_np 	= Interpolation.linearInterpolation2D(AoA, Mach, CNp, Alpha, Ma);
	c_nr 	= Interpolation.linearInterpolation2D(AoA, Mach, CNr, Alpha, Ma);
	//c_nzeta = CNzeta;
	*/
	alpha	= Alpha * PI / 180;
	beta	= Beta * PI / 180;
	eta		= ETA * PI / 180;
	xi		= XI * PI / 180;
	zeta	= ZETA * PI / 180;

	C_A = c_a + c_aq * q + c_aEta *eta;

	C_W = c_w + c_weta * eta;

	C_Q = 0; // noch ergänzen

	//C_L = c_l + c_lp * p + c_lr * r + c_lxi * xi; // zeta term ergänzen

	C_M = c_m + c_mq * q + c_meta * eta;

	//C_N = c_n + c_np * p + c_nr *r + c_nxi + xi; // zeta term ergänzen

	C_X = -C_W * cos(alpha) * cos(beta) - C_Q  *cos(alpha) * sin(beta) + C_A * sin(alpha);
	
	C_Y = 0; // noch ergänzen

	C_Z = -C_W * sin(alpha) * cos(beta) - C_Q  *sin(alpha) * sin(beta) + C_A * cos(alpha);

	// Guidanc daten noch ergänzen

	// Kräfte und Momente

	AeroData.CA = C_A;
	AeroData.CW = C_W;
	AeroData.CM = C_M;
	AeroData.AoA = Alpha;
	AeroData.AoS = Beta;
	AeroData.Mach = Ma;


}
