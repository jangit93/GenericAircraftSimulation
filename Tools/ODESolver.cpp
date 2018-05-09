typedef double Float64;
#pragma once
template <typename T>
T EulerIntegration(T v1, T v2, Float64 dt) {
	v1 = v1 + dt*v2;
	return v1;
}