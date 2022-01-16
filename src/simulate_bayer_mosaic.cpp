#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
	const std::vector<unsigned char>& rgb,
	const int& width,
	const int& height,
	std::vector<unsigned char>& bayer)
{
	bayer.resize(width * height);
	////////////////////////////////////////////////////////////////////////////
	//This algorithm seeks to minimize the variance of the color between demosaiced and rgb, and the least amount of noise points
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
			//cross area
			int crs_avg =
				(up ? rgb[((i - 1) * width + j) * 3 + int(state)] : 0) +
				(down ? rgb[((i + 1) * width + j) * 3 + int(state)] : 0) +
				(lef ? rgb[(i * width + j - 1) * 3 + int(state)] : 0) +
				(rig ? rgb[(i * width + j + 1) * 3 + int(state)] : 0);
			crs_avg /= (up + down + lef + rig);
			if (state == Color::G) {
				//the ratio is defined by 1(4 * 1/4 cross position will used this color later) : 1(1 * 1 self)
				bayer[i * width + j] = int((crs_avg + (rgb[(i * width + j) * 3 + int(state)])) / 2);
			}
			else {
				//four corner
				int cor_avg =
					(up && lef ? rgb[((i - 1) * width + j - 1) * 3 + int(state)] : 0) +
					(up && rig ? rgb[((i - 1) * width + j + 1) * 3 + int(state)] : 0) +
					(down && lef ? rgb[((i + 1) * width + j - 1) * 3 + int(state)] : 0) +
					(down && rig ? rgb[((i + 1) * width + j + 1) * 3 + int(state)] : 0);
				if (lef + rig + up + down == 4) {
					cor_avg /= 4;
				}
				else if (lef + rig + up + down == 3) {
					cor_avg /= 2;
				}
				//the ratio is defined by 1(4 * 1/4 corner position will used this color later) : 2(4 * 1/2 cross position will used this color later) : 1(1 * 1 self)
				bayer[i * width + j] = int((cor_avg + crs_avg * 2 + rgb[(i * width + j) * 3 + int(state)]) / 4);
			}
			state = (state == Color::G) ? this_line : Color::G;
		}
		this_line = (this_line == Color::B) ? Color::R : Color::B;
	}
	////////////////////////////////////////////////////////////////////////////
}
