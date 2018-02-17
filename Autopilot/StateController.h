#pragma once
#include"MatFileReader.h"
#include"DataCloud.h"


class StateController
{

public:
	StateController();

	~StateController();

	void initStateController();

	void updateStateController();

	
	
private:

	// parameters of matFileReader
	AutopilotStruct * StateControllertData;
	matvar_t MatFileData;
	MatFileReader *readAutopilotData;
	int Fields;
	int start;
	int stride;
	int edge;
	int copy_field;

};