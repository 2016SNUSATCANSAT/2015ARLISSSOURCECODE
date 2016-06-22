// 2015_ARLISS SNUSAT
// Stereo Camera Code
// Han-Byul Kim, Kwon
// Edited 2015.08.09

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

/*char *itoa(long i, char *s, int dummy_radix)
{
	sprintf(s, "%ld", i);
	return s;
}*/


char* timeToString(struct tm *t);

int main(){
	IplImage* frame1;
	CvCapture* cam1;
	char a[100];
	char num[100];
	int i = 1;
	char *filename;
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	char* time = timeToString(t);


//	cam1 = cvCaptureFromCAM(0);

//	cvNamedWindow("sample1", CV_WINDOW_AUTOSIZE);

//	cin >> str;

//	while (str == 'c'){
//	while (1){
		cam1 = cvCaptureFromCAM(0);
		cvNamedWindow("sample1", CV_WINDOW_AUTOSIZE);
		frame1 = cvQueryFrame(cam1);

		if (!frame1)
//			break;

		cvShowImage("sample1", frame1);
		
		sprintf(a, "%s%s", time, ".jpg");
		//printf("%s", a);
		filename = a;
		cvSaveImage(filename, frame1);

		if (cvWaitKey(10) >= 0)
//			break;
		i++;
	
	
		cvReleaseCapture(&cam1);
		cvDestroyWindow("sample1");
//		cin >> str;
//	}
//cvReleaseCapture(&cam1);
//cvDestroyWindow("sample1");
	return 0;
}


char* timeToString(struct tm *t)
{
	static char s[20];
	sprintf(s, "%04d_%02d_%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon+1, t-> tm_mday, t-> tm_hour, t-> tm_min, t -> tm_sec);
	return s;
}
