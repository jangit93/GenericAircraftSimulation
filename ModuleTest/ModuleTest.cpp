#include"Atmosphere.h"
#include"DataLogger.h"

void AtmosphereTest()
{
	Atmopshere *Atmo = new Atmopshere;
	AtmosphereStruct Atmos;

	Float64 Altitude;
	DataLogger logAtmoTestData("AtmosphereTestData.txt", 25, " ");

	logAtmoTestData.add("Altitude", Altitude);
	logAtmoTestData.add("Rho", Atmos.rho);
	logAtmoTestData.add("Temperture", Atmos.Temperature);
	logAtmoTestData.add("Pressure", Atmos.Pressure);
	logAtmoTestData.add("SpeedOfSound", Atmos.speedOfSound);

	logAtmoTestData.printHeader();

	Atmo->initAtmosphere();
	for (Altitude = 0; Altitude < 10000; Altitude++) {
		Atmo->updateAtmosphere(Altitude, Atmos);
		logAtmoTestData.print();
	}

	std::cout << "Atmosphere Test beendet" << std::endl;
};
int main()
{
	
	AtmosphereTest();

	system("pause");
}

