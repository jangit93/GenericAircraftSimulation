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
	virtual void initNavigation();

	/**
	* \brief update function of a flawless navigation module
	*	@param	FlightTime			flighttime
	*	@param	NavData				structure of navigation data
	*	@param	AirframeData		structure of flight states
	*/
	virtual void updateNavigation(Float64 FlightTime,
									NavigationStruct &NavData,
								  AirframeStruct &AirframeData);
private:

};
