#pragma once
#include<Eigen/dense>
#include<iostream>
#include"DataCloud.h"
#include"MatFileReader.h"
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

class FindNeighbor
{
public:

	FindNeighbor();

	~FindNeighbor();

	void initFindNeighbor();

	Eigen::Vector4d BlendingParameters(AirframeStruct &AirframeData);

	Eigen::MatrixXd combineVec(Eigen::Vector2d &Alt, 
							   Eigen::Vector2d &Vel);
	
	
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