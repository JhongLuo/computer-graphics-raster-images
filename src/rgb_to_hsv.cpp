#include "rgb_to_hsv.h"
#include <math.h>
void rgb_to_hsv(
	const double r,
	const double g,
	const double b,
	double& h,
	double& s,
	double& v)
{
	////////////////////////////////////////////////////////////////////////////
	double r_v = r / 255;
	double g_v = g / 255;
	double b_v = b / 255;

	double min_v = r_v;
	if (g_v < min_v)
		min_v = g_v;
	if (b_v < min_v)
		min_v = b_v;

	double max_v = r_v;
	char max_c = 'r';
	if (g_v > max_v) {
		max_v = g_v;
		max_c = 'g';
	}
	if (b_v > max_v) {
		max_v = b_v;
		max_c = 'b';
	}

	double delta = max_v - min_v;
	if (delta < 0.001) {
		delta = 0;
	}
	if (delta == 0) {
		h = 0;
	}
	else if (max_c == 'r') {
		if (g_v >= b_v) {
			h = 60 * (g_v - b_v) / delta;
		}
		else {
			h = 60 * ((g_v - b_v) / delta + 6);
		}
	}
	else if (max_c == 'g') {
		h = 60 * ((b_v - r_v) / delta + 2);
	}
	else {
		h = 60 * ((r_v - g_v) / delta + 4);
	}

	if (max_v < 0.001) {
		s = 0;
	}
	else {
		s = delta / max_v;
	}

	v = max_v;
	////////////////////////////////////////////////////////////////////////////
}
