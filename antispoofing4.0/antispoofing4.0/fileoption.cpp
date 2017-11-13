#include "fileoption.h"

void normalize(int *src, float* dst, int size)
{
	int max = 0;
	for (int i = 0;i < size;i ++)
		if (src[i] > max) 
			max = src[i];
	for (int i = 0;i < size;i ++)
		dst[i] = (float)src[i] / max;
}

void write_to_file(IplImage *src,char *filename)
{
	IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);
	uchar *data=(uchar*)src -> imageData;

	int step=src->widthStep;

	ofstream outputfile;
	outputfile.open(filename,ios::app);

	for (int i = 0;i < src -> height;i++)
		for (int j = 0;j < src -> width;j++)
	{	
		outputfile << (int)data[i*step + j] << ' ';
	}

	outputfile.close();
}

void write_to_file(int *data, int length, char* filename)
{
	ofstream outputfile;
	outputfile.open(filename,ios::app);

	for (int i = 0;i < length;i++)
	{
		outputfile << (int)data[i] << ' ';
	}
	outputfile.close();
}

void write_to_file(float *data, int length, char* filename)
{
	ofstream outputfile;
	outputfile.open(filename,ios::app);

	for (int i = 0;i < length;i++)
	{
		outputfile << data[i] << ' ';
	}
	outputfile.close();
}