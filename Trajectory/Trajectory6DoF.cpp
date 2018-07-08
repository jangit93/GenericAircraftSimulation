#include "Trajectory6DoF.h"

Trajectory6Dof::Trajectory6Dof(SimDPreference &Simpref):Trajectory3Dof(Simpref)
{
	
	airframe	= new Airframe;
	guidance	= new Guidance(Simpref);
	autopilot	= new Autopilot;
	dt			= Simpref.dt;

	logNavData		= new DataLogger("NavigationData.txt", 25, " ");
	logActuatorData = new DataLogger("ActuatorData.txt", 25, " ");
	logIMUData		= new DataLogger("IMUData.txt", 25, " ");

}

Trajectory6Dof::~Trajectory6Dof()
{

}

void Trajectory6Dof::initTrajectory(Float64 &FlightTime, 
									AerodynamicStruct & AeroData,
									AirframeStruct & AirframeData,
									ThrustStruct & ThrustData,
									AircraftStruct &AircraftData,
									GuidanceStruct & GuidanceData,
									NavigationStruct &NavData,
									ActuatorStruct &ActuatorData,
									IMUStruct &IMUData)
{


	initTrajectory3DoF(FlightTime,
						AeroData,
						AirframeData,
						ThrustData,
						AircraftData);

	autopilot->initAutopilot();

	guidance->initGuidance(FlightTime,
							GuidanceData,
							AircraftData);

	initLog6Dof(FlightTime,
				IMUData,
				NavData,
				ActuatorData);

}


void Trajectory6Dof::updateTrajectory(Float64 FlightTime, 
									  AtmosphereStruct & AtmoData,
									  AerodynamicStruct & AeroData, 
									  AirframeStruct & AirframeData, 
									  ThrustStruct & ThrustData, 
									  GuidanceStruct & GuidanceData, 
									  NavigationStruct & NavData, 
									  ActuatorStruct & ActuatorData, 
									  IMUStruct & IMUData)
{

	integrationTrajectory(AirframeData,
						  IMUData,
						  NavData);



	updateTrajectory3DoF(FlightTime,
						AtmoData,
						AeroData,
						AirframeData,
						ThrustData,
						ActuatorData,
						IMUData,
						NavData);

	airframe->updateRotatory(AeroData,
							ThrustData,
							AirframeData);

	guidance->updateGuidance(FlightTime,
							AeroData,
							ThrustData,
							AirframeData,
							GuidanceData);

	autopilot->updateAutopilot(FlightTime,
								AirframeData,
								AeroData,
								GuidanceData,
								ActuatorData,
								IMUData,
								NavData);
	log6DofData();
}


void Trajectory6Dof::integrationTrajectory(AirframeStruct & AirframeData,
										   IMUStruct&IMUData,
										   NavigationStruct &NavData)
{
	AirframeData.velNED = EulerIntegration(AirframeData.velNED, AirframeData.accTransNED, dt);
	AirframeData.posNED = EulerIntegration(AirframeData.posNED, AirframeData.velNED, dt);

	IMUData.accTransNED			= AirframeData.accTransNED;
	AirframeData.rotRatesBody	= EulerIntegration(AirframeData.rotRatesBody, AirframeData.accRotBody, dt);
	IMUData.rotRatesBody		= AirframeData.rotRatesBody;
	AirframeData.EulerAngles	= EulerIntegration(AirframeData.EulerAngles, AirframeData.Eulerdot, dt);

	NavData.EulerAngles = AirframeData.EulerAngles;
	NavData.absVel		= AirframeData.velBody.norm();
	NavData.velNED		= AirframeData.velNED;
	NavData.posNED		= AirframeData.posNED;

	AirframeData.Gamma	= atan2(-AirframeData.velNED(2), sqrt(AirframeData.velNED(0)*AirframeData.velNED(0) + AirframeData.velNED(1)*AirframeData.velNED(1)));
	AirframeData.Chi	= atan2(AirframeData.velNED(1), AirframeData.velNED(0));

	AirframeData.matNEDToBody = Trafo.MatNedToBody(AirframeData.EulerAngles(0), AirframeData.EulerAngles(1), AirframeData.EulerAngles(2));
	AirframeData.matBodyToNED = Trafo.MatBodyToNED(AirframeData.matNEDToBody);
	AirframeData.matNEDToTraj = Trafo.MatNEDToTrajectory(AirframeData.Gamma, AirframeData.Chi);

}


void Trajectory6Dof::log6DofData()
{	
	log3DofData();

	guidance->logGuidanceData();

	logNavData->print();

	logIMUData->print();

	logActuatorData->print();
}

void Trajectory6Dof::initLog6Dof(Float64 & FlightTime, 
								 IMUStruct & IMUData, 
								 NavigationStruct & NavData, 
								 ActuatorStruct & ActuatorData)
{
	logNavData->add("Flight Time", FlightTime);
	logNavData->add("Velocity_abs", NavData.absVel);
	logNavData->add("posNed_x", NavData.posNED(0));
	logNavData->add("posNed_y", NavData.posNED(1));
	logNavData->add("posNed_z", NavData.posNED(2));
	logNavData->add("phi", NavData.EulerAngles(0));
	logNavData->add("theta", NavData.EulerAngles(1));
	logNavData->add("psi", NavData.EulerAngles(2));

	logNavData->printHeader();
	
	logActuatorData->add("Eta", ActuatorData.Eta);
	logActuatorData->add("Zeta", ActuatorData.Zeta);
	logActuatorData->add("Xi", ActuatorData.Xi);
	logActuatorData->add("Delta", ActuatorData.Delta);

	logActuatorData->printHeader();

	logIMUData->add("p", IMUData.rotRatesBody(0));
	logIMUData->add("q", IMUData.rotRatesBody(1));
	logIMUData->add("r", IMUData.rotRatesBody(2));
	logIMUData->add("acc_x_NED", IMUData.accTransNED(0));
	logIMUData->add("acc_y_NED", IMUData.accTransNED(1));
	logIMUData->add("acc_z_NED", IMUData.accTransNED(2));

	logIMUData->printHeader();
}