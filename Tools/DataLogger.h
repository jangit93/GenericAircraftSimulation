/** @defgroup	Tools Tools
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Data Logger is a class to write simulation data to an outputfile.
*  @{
*/

#ifndef DATALOGGER_H
#define DATALOGGER_H

#include<vector>
#include<fstream>
#include<string>
#include"../eigen/Eigen/dense"
#include<iomanip>

#include<sstream>
#include <iostream>
#include <string>
#include <cmath>


class DataLogger
{
public:
	/**
	* \brief constructor
	*/
	DataLogger(std::string aPath, int aWidth, std::string aDelimiter);

	/**
	* \brief Destructor
	*/
	~DataLogger();

	/**
	* \brief defines variable which is stored in outputfile (double)
	*/
	void add(std::string aHeader, double &aVar);

	/**
	* \brief defines variable which is stored in outputfile (integer)
	*/
	void add(std::string aHeader, int &aVar);  


	/**
	* \brief  writes defined variable to an outputfile
	*/
	void print();

	/**
	* \brief defines header of specific variable
	*/
	void printHeader();

	std::string to_string1(double value);

	std::string to_string2(double value);
	std::string to_string3(double value);


private:
	std::vector<double*> doubleVec;
	std::vector<std::string> doubleHeader;
	int mNumberDoubles;

	std::vector<int*> intVec;
	std::vector<std::string> intHeader;
	int mNumberInts;

	std::string str;
	std::ofstream mStream;

	int mWidth;
	std::string mDelimiter;
	char buffer[10];
};

#endif DATALOGGER_H
/**@}*/