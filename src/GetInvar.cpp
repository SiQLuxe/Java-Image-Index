/*
 * GetInvar.cpp
 *
 *  Created on: Apr 29, 2012
 *      Author: luxe
 */

#include "GetInvar.h"
using namespace cv;

const double PI = 3.14159265358979323846;
const int P = 8;


GetInvar::GetInvar() {
	// TODO Auto-generated constructor stub
	for(int i=0; i<256; ++i){
		igin[i]=0;
	}
}

GetInvar::~GetInvar() {
	// TODO Auto-generated destructor stub
}

double GetInvar::cround(double r) {
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
unsigned char GetInvar::rol(unsigned char &val) {
	int highbit;
	if (val & 0x80)
		highbit = 1;
	else
		highbit = 0;
	val <<= 1;
	val |= highbit;
	return val;
}

bool GetInvar::IsVaild(Mat img) {
	if (img.rows * img.cols < 1)
		return false;
	return true;
}

void GetInvar::GrayInvar(Mat img) {
	if (!IsVaild(img))
		return;

	for (int i = 1; i < img.rows - 1; ++i) {
		for (int j = 1; j < img.cols - 1; ++j) {
			int LBP = 0;
			int neighborP = 0;
			int centerP = img.at<uchar>(i, j);
			for (int p = 0; p < P; ++p) {
				neighborP = img.at<uchar>(i - cround(cos(2 * PI * p / P)),
						j + cround(sin(2 * PI * p / P)));
				neighborP = neighborP < centerP ? 0 : 1;
				LBP |= neighborP << p;
			}
			igin[LBP]++;
		}
	}

}
void GetInvar::RotationInvar(Mat img, float* drin) {
	if (!IsVaild(img))
		return;

	int tempr[256] = { 0 };
	for (int i = 0; i < 256; ++i) {
		unsigned char max = i, temp = i;
		for (int j = 1; j < P; ++j) {
			rol(temp);
			max = temp > max ? temp : max;
		}
		tempr[max] += igin[i];
	}

	int index = 0;
	for (int k = 0; k < 256; ++k) {
		if (tempr[k] != 0) {
			drin[index] = tempr[k];
			index++;
		}
	}

	for (int n = 0; n < 36; ++n) {
		drin[n] /= (img.cols * img.rows/5.0);
//		iirin[n] = ceil(drin[n] * 256 - 0.5);
	}
}

void GetInvar::GrayHistog(Mat img, float* dgin) {
	if (!IsVaild(img))
		return;

	int index = -1;
	for (int i = 0; i < 256; ++i) {
		if (i % 4 == 0)
			index++;
		dgin[index] += igin[i];
	}
	for (int k = 0; k < 64; ++k) { //
		dgin[k] /= (img.cols * img.rows/5.0);
//		iigin[k] = ceil(dgin[k] * 256 - 0.5);
	}
}
