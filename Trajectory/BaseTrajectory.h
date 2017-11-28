/** @ingroup	Trajectory Trajectory
*	@author		Jan Olucak
*	@date		28.11.2017
*	@version	1.0
*
*	BaseTrajectory is the superclass for all trajectory classes.
*  @{
*/

#ifndef BASETRAJECTORY_H
#define BASETRAJECTORY_H

class BaseTrajectory {
public:

	BaseTrajectory();

	~BaseTrajectory();

	void initTrajectory();

	void updateTrajectory();

	virtual void initializeTrajectory();

	virtual void calcTrajectory();


private:
	


};

#endif