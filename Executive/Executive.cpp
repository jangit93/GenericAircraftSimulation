#include"readInData.h"
#include"LinearInterpolation.h"
#include"Atmosphere.h"
#include"DataLogger.h"
#include"DataCloud.h"
#include"ThrustAnalytical.h"
#include<Map>
#include<math.h>
#include <iostream>
#include <time.h> 


template <typename T>
T Euler(T v1, T v2) {
	v1 = v1 + 0.01*v2;
	return v1;
}
int main(int argv, char* argc[])
{
	double time1 = 0.0, tstart;      // time measurment variable

		tstart = clock();              // start 


		ThrustAnalytical Thrusttest;
		Thrusttest.initThrust();


	time1 += clock() - tstart;     // end
	time1 = time1 / CLOCKS_PER_SEC;  // rescale to seconds

	std::cout << "Simulationszeit = " << time1 << " sec." << std::endl;

	system("Pause");

}

