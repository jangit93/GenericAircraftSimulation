/*
* Copyright (C) 2013   Christopher C. Hulbert
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY CHRISTOPHER C. HULBERT ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER C. HULBERT OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

/** @ingroup	Tools
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	MatFileReader class provides functions to read in compressed .mat-Files. All 
*   functions are based in the main on the matio library of Christopher C. Hulbert (see above copyright)
*  @{
*/

#ifndef MATFILEREADER_H
#define MATFILEREADER_H

#include<iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include"../matio/getopt/getopt.h"
#include "../matio/src/matio.h"
#include<algorithm>
#include<Eigen\dense>
#include<tuple>
#include"IndependetDataTypes.h"
#include<vector>

class MatFileReader
{
public:
	/**
	* \brief constructor
	* @param filename name of specific .mat-file
	*/
	MatFileReader(const char *filename);

	/**
	* \brief destructor
	*/
	~MatFileReader();

	/**
	* \brief reads in .mat files that cotains of structures (specific for gain scheduling controller)
	* @param FieldName name of desired field 
	* @param start 
	* @param stride
	* @param edge
	* @param copy_fields
	*/
	std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Float64,Eigen::RowVectorXd> readMatFileStructure(const char *FieldName,
																								  int &start, 
																								  int &stride, 
																								  int &edge, 
																								  int &copy_fields);
	/**
	* \brief reads in .mat files that cotains only variables
	* @param FieldName name of desired field

	*/
	std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Float64, Eigen::RowVectorXd> readMatFileData(const char *FieldName);

	/**
	* \brief get basic information about the .mat-file
	* @param MatFileName name of .mat-File
	*/
	matvar_t getMatFileInfo(const char *MatFileName);

private:
	char PathName;
	Float64 value;
	Eigen::MatrixXd matrix;
	Eigen::VectorXd vector;
	Eigen::RowVectorXd row_vector;
	int   err;
	mat_t    *mat;
	matvar_t *matvar, *stru, *field;
	size_t ing_index;
	int read_err;



};
#endif MATFILEREADER_H