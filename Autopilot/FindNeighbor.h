/**
*	@ingroup Autopilot
*	@author Jan Olucak
*	@date 01.05.2018
*	@version 1.0
*
*	FindNeighbor class calculates parameters for gain scheduling. 
*
*/

#ifndef FINDNEIGHBOR_H
#define FINDNEIGHBOR_H

#include<iostream>
#include"DataCloud.h"
#include"MatFileReader.h"
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

class FindNeighbor
{
public:
	/**
	* \brief constructor
	*/
	FindNeighbor();

	/**
	* \brief destructor
	*/
	~FindNeighbor();

	/**
	* \brief trim states are read in 
	*/
	void initFindNeighbor();

	/**
	* \brief blending parameters  for gain scheduing are calculated
	*	@param NavData	structure of airframe parameters 
	*/
	std::tuple<Eigen::Vector4d,Eigen::MatrixXd> BlendingParameters(NavigationStruct &NavData);

	/**
	* \brief help function to combine vectors for gain scheduling
	*	@param Alt	Vector of altitude
	*	@param Vel	Vector of velocity
	*/
	Eigen::MatrixXd combineVec(Eigen::Vector2d &Alt, 
							   Eigen::Vector2d &Vel);

	/**
	* \brief help functions to find index
	* @param	row		desired row
	* @param	column	desired column
	* @param	rows	total number of rows
	* @param	columns	total number of columns
	*/
	int sub2ind(const int row, 
				const int column, 
				const int rows, 
				const int columns);
	
	
private:
	// parameters of matFileReader
	AutopilotStruct *neighbors;
	matvar_t MatFileData;
	int Fields;
	int start;
	int stride;
	int edge;
	int copy_field;

	Eigen::Vector2d tempVel;
	Float64 minVel;
	Float64 maxVel;
	Eigen::Vector2d tempAlt;
	Float64 minAlt;
	Float64 maxAlt;
	Eigen::MatrixXd Neighbor;

	Eigen::MatrixXd comb;
	Eigen::VectorXd Vec1;
	Eigen::VectorXd  Vec2;

	Eigen::Vector2d xi;
	Eigen::Vector2d phi_j;
	Eigen::Vector4d phi;

};
#endif // !FINDNEIGHBOR_H