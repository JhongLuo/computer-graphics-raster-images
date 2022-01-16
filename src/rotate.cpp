#include "rotate.h"

void rotate(
	const std::vector<unsigned char>& input,
	const int width,
	const int height,
	const int num_channels,
	std::vector<unsigned char>& rotated)
{
	rotated.resize(height * width * num_channels);
	////////////////////////////////////////////////////////////////////////////
	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			for (int k = 0;k < num_channels;k++) {
				rotated[((width - 1 - j) * height + i) * num_channels + k] = input[(i * width + j) * num_channels + k];
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
