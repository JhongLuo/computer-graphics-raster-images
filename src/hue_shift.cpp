#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include<math.h>
void hue_shift(
	const std::vector<unsigned char>& rgb,
	const int width,
	const int height,
	const double shift,
	std::vector<unsigned char>& shifted)
{
	shifted.resize(rgb.size());
	////////////////////////////////////////////////////////////////////////////
	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			double h, s, v;
			unsigned int seq = (i * width + j) * 3;
			rgb_to_hsv(rgb[seq], rgb[seq + 1], rgb[seq + 2], h, s, v);
			h = fmod((h + 180), 360);
			double r, g, b;
			hsv_to_rgb(h, s, v, r, g, b);
			shifted[seq] = r;
			shifted[seq + 1] = g;
			shifted[seq + 2] = b;
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
