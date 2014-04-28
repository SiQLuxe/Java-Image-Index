/*
 * GetInvar.h
 *
 *  Created on: Apr 29, 2012
 *      Author: luxe
 */

#ifndef GETINVAR_H_
#define GETINVAR_H_

#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>


class GetInvar {
private:
	int igin[256];	//primitive gray statistical
//	double dgin[64]; //double gray invariance
//	double drin[36]; //double rotation invariance
public:
	GetInvar();
	double cround(double r);
	unsigned char rol(unsigned char &val);
	bool IsVaild(cv::Mat img);

	void GrayInvar(cv::Mat img);
	void RotationInvar(cv::Mat img, float* drin);

	void GrayHistog(cv::Mat img, float* dgin);
	virtual ~GetInvar();
};

#endif /* GETINVAR_H_ */
