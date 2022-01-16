#include "rgb_to_gray.h"

void rgb_to_gray(
	const std::vector<unsigned char>& rgb,
	const int width,
	const int height,
	std::vector<unsigned char>& gray)
{
	gray.resize(height * width);
	////////////////////////////////////////////////////////////////////////////
	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			unsigned int seq = (i * width + j) * 3;
			//299 : 587 : 114
			gray[i * width + j] = (rgb[seq] * 299.0 + rgb[seq + 1] * 587.0 + rgb[seq + 2] * 114.0) / 1000;
		}
	}
	////////////////////////////////////////////////////////////////////////////
}


