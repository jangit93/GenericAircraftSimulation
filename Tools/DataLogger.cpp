#include"DataLogger.h"


DataLogger::DataLogger(std::string Path, 
					   int Width, 
					   std::string Delimiter)
{
	mWidth = Width;
	mDelimiter = Delimiter;
	std::string PathName = "../Output/";
	mStream.open(PathName+Path);
	
	mStream << std::setiosflags(std::ios::left);

	mNumberDoubles = 0;
	mNumberInts = 0;
	
}

DataLogger::~DataLogger()
{
	mStream.close();
}

void DataLogger::add(std::string Header, 
					 Float64 & Var)
{
	doubleHeader.push_back(Header);
	doubleVec.push_back(&Var);
	mNumberDoubles++;
}

void DataLogger::add(std::string Header, 
					 int & Var)
{
	intHeader.push_back(Header);
	intVec.push_back(&Var);
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


std::string DataLogger::to_string2(Float64 value)
{
	char buffer[80] = {};
	sprintf_s(buffer, "%f", value);
	std::string s = buffer;
	return s;
}