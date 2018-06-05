/**
*	@ingroup Navigation
*	@author Jan Olucak
*	@date 02.01.2018
*	@version 1.0
*
*	BaseNavigation class is the superclass for all Navigation models. Using pointer to base
*	init and update function allows the user to extend the Navigation module with new
*	models.
*
*/
#ifndef BASENAVIGATION_H
#define BASENAVIGATION_H




#include"../DataCloud/DataCloud.h"

class BaseNavigation
{
public:
	/**
	* \brief constructor
	*/
	BaseNavigation();

	/**
	* \brief destructor
	*/
	~BaseNavigation();


	/**
	* \brief initialize navigation
	*/
	virtual void initNavigation(NavigationStruct & NavData);

	/**
	* \brief call to desired update function
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*	@param	AirframeData		structure of flight states
	*/
	virtual void updateNavigation(Float64 FlightTime, 
						  NavigationStruct &NavData,
						  AirframeStruct &AirframeData);




private:

};
#endif // !BASENAVIGATION_H