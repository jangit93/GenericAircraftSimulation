/** @defgroup	Navigtion Navigation
*	@author		Jan Olucak
*	@date		01.05.2018
*	@version	1.0
*
*	Navigation class is used to call the desired navigation model. The navigation model is selected from
*	General.dat input file.
*  @{
*/

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include"IndependetDataTypes.h"
#include"BaseNavigation.h"
#include"DataCloud.h"
#include"flawlessNavigation.h"


class Navigation
{
public:
	/**
	* \brief constructor
	*	@param	SimPref		structure of model selctions
	*/
	Navigation(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Navigation();

	/**
	* \brief set pointer to desired class
	*	@param	Type navigation Model Selection
	*/
	void selectNavigation(int Type);

	/**
	* \brief call to desired init-function
	*/
	void initNavigation(Float64 & FlightTime,
						NavigationStruct & NavData,
						IMUStruct &IMUData);

	/**
	* \brief call to desired update function
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*	@param	AirframeData		flight states
	*   @param  IMUData				structure of acceleratiosn and rotatory rates
	*/
	void updateNavigation(Float64 FlightTime,
						  NavigationStruct &NavData,
						  AirframeStruct &AirframeData,
						  IMUStruct &IMUData);

	/**
	* \brief data logger for navigation data
	*/
	void logNavigationData();

private:
	BaseNavigation * navigation;
};
/**@}*/
#endif // !NAVIGATION_H
