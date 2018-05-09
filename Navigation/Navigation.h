/** @defgroup	Navigtion Navigation
*	@author		Jan Olucak
*	@date		02.01.2018
*	@version	1.0
*
*	Navigation class is used to call the desired navigation model. The navigation model is selected from
*	General.dat input file.
*  @{
*/

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include<Eigen/dense>
#include"IndependetDataTypes.h"
#include"BaseNavigation.h"
#include"DataCloud.h"
#include"flawlessNavigation.h"

class Navigation
{
public:
	/**
	* \brief constructor
	*	@param	SimPref			structure of model selctions
	*/
	Navigation(SimDPreference &SimPref);

	/**
	* \brief destructor
	*/
	~Navigation();

	/**
	* \brief set pointer to desired class
	*	@param	type			Aerodynamic Model Selection
	*/
	void selectNavigation(int Type);

	/**
	* \brief call to desired init-function
	*/
	void initNavigation();

	/**
	* \brief call to desired update function
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*	@param	GuidanceData		structure of guidance data
	*/
	void updateNavigation(Float64 FlightTime,
						NavigationStruct & NavData,
						AirframeStruct &AirframeData);

private:
	BaseNavigation * navigation;
};
/**@}*/
#endif // !NAVIGATION_H
