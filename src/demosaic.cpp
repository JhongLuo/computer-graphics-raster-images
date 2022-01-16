#include "demosaic.h"

void demosaic(
	const std::vector<unsigned char>& bayer,
	const int& width,
	const int& height,
	std::vector<unsigned char>& rgb)
{
	rgb.resize(width * height * 3);
	////////////////////////////////////////////////////////////////////////////
	enum class Color {
		R = 0, G = 1, B = 2
	}state = Color::G, this_line = Color::B;

	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			//get the pixel's position type
			bool lef = (j - 1 > 0) ? true : false;
			bool rig = (j + 1 < width) ? true : false;
			bool up = (i - 1 > 0) ? true : false;
			bool down = (i + 1 < height) ? true : false;
			//vertical
			int ver_avg = ((up ? bayer[(i - 1) * width + j] : 0) + (down ? bayer[(i + 1) * width + j] : 0)) / (up + down);
			//horizental
			int hor_avg = ((lef ? bayer[i * width + j - 1] : 0) + (rig ? bayer[i * width + j + 1] : 0)) / (lef + rig);
			//four corner
			int cor_avg =
				(up && lef ? bayer[(i - 1) * width + j - 1] : 0) +
				(up && rig ? bayer[(i - 1) * width + j + 1] : 0) +
				(down && lef ? bayer[(i + 1) * width + j - 1] : 0) +
				(down && rig ? bayer[(i + 1) * width + j + 1] : 0);
			if (lef + rig + up + down == 4) {
				cor_avg /= 4;
			}
			else if (lef + rig + up + down == 3) {
				cor_avg /= 2;
			}

			if (state == Color::G) {
				rgb[(i * width + j) * 3 + int(Color::R)] = this_line == Color::R ? hor_avg : ver_avg;
				rgb[(i * width + j) * 3 + int(Color::B)] = this_line == Color::B ? hor_avg : ver_avg;
			}
			else {
				rgb[(i * width + j) * 3 + int(Color::G)] = (ver_avg + hor_avg) / 2;
				rgb[(i * width + j) * 3 + int(state == Color::B ? Color::R : Color::B)] = cor_avg;
			}
			//itself
			rgb[(i * width + j) * 3 + int(state)] = bayer[i * width + j];

			state = (state == Color::G) ? this_line : Color::G;
		}
		this_line = (this_line == Color::B) ? Color::R : Color::B;
	}
	////////////////////////////////////////////////////////////////////////////
}
