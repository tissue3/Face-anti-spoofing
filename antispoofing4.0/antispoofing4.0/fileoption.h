#include <opencv2/opencv.hpp>
#include <cv.h> 
#include <highgui.h>
#include <cxcore.h>
#include <fstream>
#include <iostream>

using namespace std;

void normalize(int *src, float* dst, int size);

void write_to_file(IplImage *src,char *filename);
void write_to_file(int *data, int length, char* filename);
void write_to_file(float *data, int length, char* filename);