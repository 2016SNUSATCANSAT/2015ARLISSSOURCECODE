// 2015_ARLISS SNUSAT
// Stereo Camera Code
// Han-Byul Kim, Kwon
// Edited 2015.08.06

#include<opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<iostream>
#include<vector> 
#include <stdio.h>
#include <fstream>
#include<time.h>
#include "/usr/include/opencv/highgui.h"
#include <string>
#include "/usr/include/opencv/cv.h"
#include <ctype.h>
#include <math.h>
#include <sstream> 
#include <cv.h>
#include <highgui.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

char *itoa(long i, char *s, int dummy_radix)
{
	sprintf(s, "%ld", i);
	return s;
}

int main(){
	IplImage* frame1;
	CvCapture* cam1;
	char a[100];
	char num[100];
	int i = 1;
	char *filename;
	char str;
//	cam1 = cvCaptureFromCAM(0);

//	cvNamedWindow("sample1", CV_WINDOW_AUTOSIZE);

	cin >> str;

	while (str == 'c'){
//	while (1){
		cam1 = cvCaptureFromCAM(0);
		cvNamedWindow("sample1", CV_WINDOW_AUTOSIZE);
		frame1 = cvQueryFrame(cam1);

		if (!frame1)
			break;

		cvShowImage("sample1", frame1);
		itoa(i, num, 10);
		sprintf(a, "%s%s", num, ".jpg");
		//printf("%s", a);
		filename = a;
		cvSaveImage(filename, frame1);

		if (cvWaitKey(10) >= 0)
			break;
		i++;
	
	
		cvReleaseCapture(&cam1);
		cvDestroyWindow("sample1");
		cin >> str;
	}
//cvReleaseCapture(&cam1);
//cvDestroyWindow("sample1");
	return 0;
}
