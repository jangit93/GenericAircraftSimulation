#include "LinearInterpolation.h"

LinearInterpolation::LinearInterpolation()
{
	index1 = 0;
	index2 = 0;
	Index = 0;
}

LinearInterpolation::~LinearInterpolation()
{
}

Float64 LinearInterpolation::searchIndex(VectorXd &Vector, 
										 Float64 &Value, 
										 Int32 &aIndex)
{
	index = 0;

	if (Value >= Vector(index)) {
		while (index < Vector.size() && Value >= Vector(index)) {
			index = index + 1;
		}
		index = index - 1;
	}
	else {
		while (Value < Vector(index) && index > 0) {
			index = index - 1;
		}
	}
	return index;
}



Float64 LinearInterpolation::linearInterpolation2D(VectorXd &Vector1,
												   VectorXd &Vector2,
												   MatrixXd &Table,
												   Float64 &Value1,
												   Float64 &Value2)
{

	index1 = searchIndex(Vector1,
						 Value1, 
						 index1);

	if (index1 != Vector1.size() - 1)
	{
		dx = (Value1 - Vector1(index1)) / (Vector1(index1 + 1) - Vector1(index1));
	}
	else
	{
		dx = 1;
		index1 = index1 - 1;
	}
	
	dx_inv = 1 - dx;

	index2 = searchIndex(Vector2,
						Value2,index2);
	if (index2 != Vector2.size() - 1)
	{
		dy = (Value2 - Vector2(index2)) / (Vector2(index2 + 1) - Vector2(index2));
	}
	else
	{
		dy = 1;
		index2 = index2 - 1;
	}
	

	dy_inv = 1 - dy;

	interpolationValue =	dx_inv	*dy_inv	*Table(index1, index2) +
							dx		*dy_inv	*Table(index1 + 1, index2) +
							dy		*dx_inv	*Table(index1, index2 + 1) +
							dx		*dy		*Table(index1 + 1, index2 + 1);

	return interpolationValue;
}

Float64 LinearInterpolation::linearInterpolation1D(VectorXd &Vector1, VectorXd &Table, Float64 &Value)
{
	Index = searchIndex(Vector1, Value,Index);

	if (Index != Vector1.size() - 1)
	{
		dx = (Value - Vector1(Index)) / (Vector1(Index + 1) - Vector1(Index));
	}
	else
	{
		dx = 1;
		Index = Index - 1;
	}
	dx_inv = 1 - dx;

	interpolationValue = Table(Index)*dx_inv + Table(Index + 1)*dx;
	return interpolationValue;
}
