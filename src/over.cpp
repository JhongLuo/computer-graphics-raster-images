#include "over.h"

void over(
	const std::vector<unsigned char>& A,
	const std::vector<unsigned char>& B,
	const int& width,
	const int& height,
	std::vector<unsigned char>& C)
{
	C.resize(A.size());
	////////////////////////////////////////////////////////////////////////////
	for (int i = 0;i < height;++i) {
		for (int j = 0;j < width;++j) {
			if (A[(i * width + j) * 4 + 3] != 0) {
				unsigned int seq = (i * width + j) * 4;
				double alpha = (A[seq + 3]) / 255.0;
				C[seq] = (unsigned char)(A[seq] * alpha + B[seq] * (1 - alpha));
				C[seq + 1] = (unsigned char)(A[seq + 1] * alpha + B[seq + 1] * (1 - alpha));
				C[seq + 2] = (unsigned char)(A[seq + 2] * alpha + B[seq + 2] * (1 - alpha));
				C[seq + 3] = 255;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
