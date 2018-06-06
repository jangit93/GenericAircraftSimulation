/** @ingroup	Tools Tools
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	Read in data provides several methods to read in parameters from specific files. 
*  @{
*/
#ifndef READINDATA_H
#define READINDATA_H


#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
//#include<Eigen/Dense>
#include"../eigen/Eigen/dense"
using Eigen::MatrixXd;
using Eigen::Vector3f;
using Eigen::MatrixX2f;
using Eigen::VectorXd;
using Eigen::Map;


typedef double Float64;

class readInData
{
public:
	/**
	* \brief constructor
	*/
	readInData();

	/**
	* \brief destructor
	*/
	~readInData();

	/**
	* \brief read in a specific value from a file
	* @param CodeWord specific name of a parameter 
	* @param Filename Name of specific file
	*/
	Float64 readInParameter(std::string CodeWord, 
							std::string Filename);

	/**
	* \brief read in tables from input file
	* @param FileName Name of specific file
	*/
	 MatrixXd readInTable(std::string FileName);

	 /**
	 * \brief read in vector from input file
	 * @param FileName Name of specific file
	 */
	VectorXd readInVector(std::string FileName);

	/**
	* \brief defines a relative path directory of input file
	* @param Pathname relative path of data file directory
	*/
	void setPath(std::string Pathname);

private:
	std::vector<double> tempData;
	int columncounter;
	double element;
	int lines;
	std::string line;
	int	columns;
	MatrixXd tempMatrix;
	VectorXd tempVec;
	std::string PathName1;
	std::string PathName2;
	Float64 tempValue;
	std::fstream input;
	std::string currtenLine;

};
#endif READINDATA_H