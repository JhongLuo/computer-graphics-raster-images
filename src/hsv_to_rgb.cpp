#include "hsv_to_rgb.h"
#include<math.h>
void hsv_to_rgb(
	const double h,
	const double s,
	const double v,
	double& r,
	double& g,
	double& b)
{
	////////////////////////////////////////////////////////////////////////////
	double C = v * s;
	double X = C * (1 - fabs(fmod(h / 60, 2) - 1));
	double m = v - C;
	if (h < 60) {
		r = C;
		g = X;
		b = 0;
	}
	else if (h < 120) {
		r = X;
		g = C;
		b = 0;
	}
	else if (h < 180) {
		r = 0;
		g = C;
		b = X;
	}
	else if (h < 240) {
		r = 0;
		g = X;
		b = C;
	}
	else if (h < 300) {
		r = X;
		g = 0;
		b = C;
	}
	else {
		r = C;
		g = 0;
		b = X;
	}
	r = (r + m) * 255;
	g = (g + m) * 255;
	b = (b + m) * 255;
	////////////////////////////////////////////////////////////////////////////
}
