#include "Transformation.h"

Transformation::Transformation()
{
}

Transformation::~Transformation()
{
}

Eigen::Matrix3d Transformation::MatNedToBody(Float64 phi, Float64 theta, Float64 psi)
{
	matNEDtoBody << cos(psi) * cos(theta), sin(psi) * cos(theta), -sin(phi),
		cos(psi)*sin(theta)*sin(phi) - sin(psi)*cos(phi), sin(psi)*sin(theta)*sin(phi) + cos(psi)*cos(phi), cos(theta)*sin(phi),
		cos(psi)*sin(theta)*cos(phi) + sin(psi)*sin(phi), sin(psi)*sin(theta)*cos(phi) - cos(psi)*sin(phi), cos(theta)*cos(phi);

	return matNEDtoBody;
}

Eigen::Matrix3d Transformation::MatBodyToNED(Eigen::Matrix3d MatNedToBody)
{
	matBodytoNED = MatNedToBody.transpose();

	return matBodytoNED;
}

Eigen::Matrix3d Transformation::MatNEDToTrajectory(Float64 gamma, Float64 chi)
{

	matNEDtoTrajectory << cos(gamma)*cos(chi)	, cos(gamma)*sin(chi)	, -sin(gamma),
							-sin(chi)			, cos(chi)				, 0,
						sin(gamma)*cos(chi)		, sin(gamma)*sin(chi)	, cos(gamma);


	return matNEDtoTrajectory;
}

Eigen::Matrix3d Transformation::MatAeroToBody(Float64 alpha, Float64 beta)
{

	matAerotoBody << cos(alpha)*cos(beta), -cos(alpha)*sin(beta),	-sin(alpha),
						sin(beta)		 ,		cos(beta)		,		0,
					 sin(alpha)*cos(beta), -sin(alpha)*sin(beta),    cos(alpha);

	return matAerotoBody;
}
