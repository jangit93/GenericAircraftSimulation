#include"DataLogger.h"


DataLogger::DataLogger(std::string aPath, int aWidth, std::string aDelimiter)
{
	mWidth = aWidth;
	mDelimiter = aDelimiter;
	std::string PathName = "../Output/";
	mStream.open(PathName+aPath);
	
	mStream << std::setiosflags(std::ios::left);

	mNumberDoubles = 0;
	mNumberInts = 0;
	
}

DataLogger::~DataLogger()
{
	mStream.close();
}

void DataLogger::add(std::string aHeader, double & aVar)
{
	doubleHeader.push_back(aHeader);
	doubleVec.push_back(&aVar);
	mNumberDoubles++;
}

void DataLogger::add(std::string aHeader, int & aVar)
{
	intHeader.push_back(aHeader);
	intVec.push_back(&aVar);
	mNumberInts++;
}


void DataLogger::print()
{
	mStream << std::setw(mWidth);
	for (int i = 0; i < mNumberDoubles; i++)
	{
		
		mStream <<  DataLogger::to_string2(*doubleVec.at(i)) + mDelimiter << std::setw(mWidth);
		
	}

	for (int i = 0; i < mNumberInts; i++)
	{
		mStream << std::to_string(*intVec.at(i)) + mDelimiter << std::setw(mWidth);
	}
	mStream << std::endl;


	
}



void DataLogger::printHeader()
{
	mStream << std::setw(mWidth);

	for (int i = 0; i < mNumberDoubles; i++)
	{
		mStream << doubleHeader.at(i) + mDelimiter << std::setw(mWidth);
	}

	for (int i = 0; i < mNumberInts; i++)
	{
		mStream << intHeader.at(i) + mDelimiter << std::setw(mWidth);
	}

	mStream << std::endl;
}

std::string DataLogger::to_string1(double value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

std::string DataLogger::to_string2(double value)
{
	char buffer[80] = {};
	sprintf_s(buffer, "%f", value);
	std::string s = buffer;
	return s;
}
/*
std::string DataLogger::to_string3(double value)
{
	std::string as_string = strtk::type_to_string<double>(value);
	return as_string;
}*/