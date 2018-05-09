#include "DataLogger.h"
#include<iostream>
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
		mStream << std::to_string(*doubleVec.at(i)) + mDelimiter << std::setw(mWidth);
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

