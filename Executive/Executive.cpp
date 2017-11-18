#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include<Map>
#include<math.h>
#include <iostream>
#include <time.h> 

int main(int argv, char* argc[])
{
	double time1 = 0.0, tstart;      // time measurment variable

		tstart = clock();              // start 

		readInData *test = new readInData;

		//MatrixXd CL = test->readInTable("CL.txt");
		/*
		Float64  mass		= test->readInParameter("mass", "Aircraft.txt");
		Float64  I_x		= test->readInParameter("I_X", "Aircraft.txt");
		Float64	 I_y		= test->readInParameter("I_Y", "Aircraft.txt");
		Float64  I_z		= test->readInParameter("I_Z", "Aircraft.txt");
		Float64  I_zx		= test->readInParameter("I_zx", "Aircraft.txt");
		Float64  wingarea	= test->readInParameter("wing_area", "Aircraft.txt");
		Float64  wingspan	= test->readInParameter("wing_span", "Aircraft.txt");
		Float64  MAC		= test->readInParameter("MAC", "Aircraft.txt");
		Float64  X_CG		= test->readInParameter("X_CG", "Aircraft.txt");
		Float64  Y_CG		= test->readInParameter("Y_CG", "Aircraft.txt");
		Float64  Z_CG		= test->readInParameter("Z_CG", "Aircraft.txt");*/
	


	//LinearInterpolation *Interp = new LinearInterpolation;
	Atmopshere *Atmo			= new Atmopshere;
	AtmosphereStruct Atmos;
/*
	MatrixXd CL = test->readInTable("CL.txt");
	
	std::cout << CL;
	VectorXd AOA = test->readInVector("AoA.txt");
	VectorXd Mach = test->readInVector("Ma.txt");

	Float64 CA = Interp->biLinearInterpolation(AOA,
		Mach,
		CL,
		2,
		0.31);

	std::cout << CA;
	*/
	Float64 Altitude;
	DataLogger logAtmo("Atmosphere.txt", 25, " ");

	logAtmo.add("Altitude", Altitude);
	logAtmo.add("Rho", Atmos.rho);
	logAtmo.add("Temperture", Atmos.Temperature);
	logAtmo.add("Pressure", Atmos.Pressure);
	logAtmo.add("SpeedOfSound", Atmos.speedOfSound);

	logAtmo.printHeader();

	Atmo->initAtmosphere();
	for (Altitude = 0; Altitude < 10000; Altitude++) {
		Atmo->updateAtmosphere(Altitude, Atmos);
		logAtmo.print();
	}
	
	



	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}

