


// 2015_ARLISS SNUSAT
// Stereo Camera Code
// Han-Byul Kim
// Edited 2015.07.24

#include <cv.h>
#include <highgui.h>
#include <string.h>
#include <stdlib.h>

void main(){
	IplImage* frame1;
	CvCapture* cam1;

	char a[100];
	char num[100];
	int i = 1;
	char *filename;

	cam1 = cvCaptureFromCAM(0);

	cvNamedWindow("sample1", CV_WINDOW_AUTOSIZE);

	while (1){
		frame1 = cvQueryFrame(cam1);

		if (!frame1)
			break;

		cvShowImage("sample1", frame1);
		_itoa(i, num, 10);
		sprintf(a, "%s%s", num, ".jpg");
		printf("%s", a);
		filename = a;
		cvSaveImage(filename, frame1);

		if (cvWaitKey(10) >= 0)
			break;
		i++;
	}
	
	cvReleaseCapture(&cam1);
	cvDestroyWindow("sample1");
}