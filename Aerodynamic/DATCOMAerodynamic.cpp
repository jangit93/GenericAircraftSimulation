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
	CAalpha = readIn->readInTable("CLA.txt");
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
	Ma = readIn->readInVector("Ma.txt");
	Xi = readIn->readInVector("Xi.txt");

}

void DATCOMAerodymamic::calcAerodynamic(Float64 FlightTime,
										AtmosphereStruct & AtmoData,
										AerodynamicStruct & AeroData,
										AirframeStruct & AirframeData,
										ThrustStruct & ThrustData)
{
	std::cout << "DATCOM Aerodynamic Update" << std::endl;
}
