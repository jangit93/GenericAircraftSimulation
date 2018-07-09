/** @ingroup	Tools
*	@author		Jan Olucak
*	@date		25.11.2017
*	@version	1.0
*
*	ODESolver provide methods for numerical integration
*  @{
*/

#include"IndependetDataTypes.h"

#ifndef ODESOLVER_CPP
#define ODESOLVER_CPP


template <typename T>
T EulerIntegration(T v1, T v2, Float64 dt) {
	v1 = v1 + dt*v2;
	return v1;
}
#endif // !ODESOLVER_CPP
/**@}*/