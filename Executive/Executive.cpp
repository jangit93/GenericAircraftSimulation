#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include"ODESolver.cpp"
#include<Map>
#include<math.h>
#include <iostream>
#include <time.h> 



int main(int argv, char* argc[])
{
	double time1 = 0.0, tstart;      // time measurment variable

		tstart = clock();              // start 


		//readInData *test = new readInData;

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
		Float64  Z_CG		= test->readInParameter("Z_CG", "Aircraft.txt");

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
		 Eigen::Vector2d v1;
		 v1(0) = 1;
		 v1(1) = 2;

		 Eigen::Vector2d v2;
		 v2(0) = 3;
		 v2(1) = 4;

	Eigen::Vector2d A = EulerIntegration(v1,v2,0.01);
	
	std::cout << A << std::endl;


	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}

