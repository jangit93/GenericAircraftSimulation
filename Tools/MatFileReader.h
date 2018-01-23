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

#pragma once

#include<iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "getopt.h"
#include"../matio/getopt/getopt.h"
#include "../matio/src/matio.h"
#include<algorithm>
#include<eigen\dense>
#include<tuple>

#include<vector>

class MatFileReader
{
public:
	MatFileReader(const char *filename);

	~MatFileReader();

	void setPath(const char Pathname);

	std::tuple<Eigen::MatrixXd, Eigen::VectorXd, double> readMatFileStructure(const char *FieldName, const char *MatFileName);

	std::tuple<Eigen::MatrixXd, Eigen::VectorXd, double> readMatFileData(const char *FieldName);

private:
	char PathName;
	double value;
	Eigen::MatrixXd matrix;
	Eigen::VectorXd vector;
	int   err;
	mat_t    *mat;
	matvar_t *matvar, *stru, *field;
	size_t ing_index;
	int read_err;



};
