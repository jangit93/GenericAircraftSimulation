#ifndef BaseThrust_H
#define BaseThrust_H

#include<math.h>
#include"DataCloud.h"
#include"readInData.h"
#include"IndependetDataTypes.h"
#include"../EIGENDIR/Eigen/Dense"


class BaseThrust {

public:
	BaseThrust();

	~BaseThrust();

	virtual void initThrust();

	virtual void updateThrust();

};

#endif	BaseThrust_H