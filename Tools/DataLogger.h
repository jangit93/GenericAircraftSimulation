#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include<vector>
#include<fstream>
#include<string>
#include<iomanip>

class DataLogger
{
public:
	DataLogger(std::string aPath, int aWidth, std::string aDelimiter);
	~DataLogger();

	void add(std::string aHeader, double &aVar);
	void add(std::string aHeader, int &aVar);   

	void print();
	void printHeader();
private:
	std::vector<double*> doubleVec;
	std::vector<std::string> doubleHeader;
	int mNumberDoubles;

	std::vector<int*> intVec;
	std::vector<std::string> intHeader;
	int mNumberInts;

	std::ofstream mStream;

	int mWidth;
	std::string mDelimiter;
};

#endif DATALOGGER_HPP
