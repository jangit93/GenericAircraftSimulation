/**
*	@ingroup Navigation
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	flawlessNavigation class is a child class of BaseNavigation. A flawless 
*	navigation module is simulated.
*
*/
#include"BaseNavigation.h"
#include"Transformation.h"
#include"ODESolver.cpp"
#include"DataLogger.h"

class flawlessNavigation :  public BaseNavigation
{
public:
	/**
	* \brief constructor
	*/
	flawlessNavigation();

	/**
	* \brief destructor
	*/
	~flawlessNavigation();

	/**
	* \brief initialize flawless navigation
	*/
	virtual void initNavigation(Float64 & FlightTime,
								NavigationStruct & NavData,
								IMUStruct &IMUData);

	/**
	* \brief update function of a flawless navigation module
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*	@param	AirframeData		structure of flight states
	*	@param	IMUData				structure with accelerations and rotatory rates
	*/
	virtual void updateNavigation(Float64 FlightTime,
								  NavigationStruct &NavData,
								  AirframeStruct &AirframeData,
								  IMUStruct &IMUData);


	/**
	* \brief data logger for navigation data
	* @param FlightTime time of flight
	* @param NavData solution of navigation estimation 
	*/
	void initlogNavigationData(Float64 & FlightTime,
								NavigationStruct &NavData,
								IMUStruct &IMUData);

	/**
	* \brief data logger for navigation data
	*/
	void logNavigationData();

private:
	Transformation * Trafo;
	DataLogger *lognavigationData;
	Float64 dt;
};
