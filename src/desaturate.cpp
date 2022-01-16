#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
	const std::vector<unsigned char>& rgb,
	const int width,
	const int height,
	const double factor,
	std::vector<unsigned char>& desaturated)
{
	desaturated.resize(rgb.size());
	////////////////////////////////////////////////////////////////////////////
	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			unsigned seq = (i * width + j) * 3;
			double h, s, v;
			rgb_to_hsv(rgb[seq], rgb[seq + 1], rgb[seq + 2], h, s, v);
			s = s * (1 - factor);
			double r, g, b;
			hsv_to_rgb(h, s, v, r, g, b);
			desaturated[seq] = r;
			desaturated[seq + 1] = g;
			desaturated[seq + 2] = b;
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
