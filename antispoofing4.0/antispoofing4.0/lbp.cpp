#include "main.h"
#include "lbp.h"
//#include "cornerdetect.h"
//原始的LBP算法

//const int sampling_step = 10;
//基于旧版本的opencv的LBP算法opencv1.0
void LBP (IplImage *src,IplImage *dst)
{
	int tmp[8]={0};
	CvScalar s;

	IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);
	uchar *data=(uchar*)src->imageData;
	int step=src->widthStep;

	//cout<<"step"<<step<<endl;

	//CvPoint2D32f corners[maxCorners];
	//findCorners(src,corners);

	for (int i = 1;i < src->height-1;i ++)
		for(int j = 1;j < src->width-1;j ++)
		{
			int sum=0;

			if(data[(i-1)*step+j-1]>data[i*step+j]) tmp[0]=1;
			else tmp[0]=0;
			if(data[i*step+(j-1)]>data[i*step+j]) tmp[1]=1;
			else tmp[1]=0;
			if(data[(i+1)*step+(j-1)]>data[i*step+j]) tmp[2]=1;
			else tmp[2]=0;
			if (data[(i+1)*step+j]>data[i*step+j]) tmp[3]=1;
			else tmp[3]=0;
			if (data[(i+1)*step+(j+1)]>data[i*step+j]) tmp[4]=1;
			else tmp[4]=0;
			if(data[i*step+(j+1)]>data[i*step+j]) tmp[5]=1;
			else tmp[5]=0;
			if(data[(i-1)*step+(j+1)]>data[i*step+j]) tmp[6]=1;
			else tmp[6]=0;
			if(data[(i-1)*step+j]>data[i*step+j]) tmp[7]=1;
			else tmp[7]=0;	
			//计算LBP编码
			s.val[0]=(tmp[0]*1+tmp[1]*2+tmp[2]*4+tmp[3]*8+tmp[4]*16+tmp[5]*32+tmp[6]*64+tmp[7]*128);
			
			cvSet2D(dst, i, j, s);//写入LBP图像
		}
	//for (int k = 0;k < maxCorners;k ++)
	//{
	//	int i = corners[k].x;
	//	int j = corners[k].y;
	//		
	//	//cout << k << ' ' << i << ' ' << j << endl;
	//	int sum=0;

	//	if(data[(i-1)*step+j-1]>data[i*step+j]) tmp[0]=1;
	//	else tmp[0]=0;
	//	if(data[i*step+(j-1)]>data[i*step+j]) tmp[1]=1;
	//	else tmp[1]=0;
	//	if(data[(i+1)*step+(j-1)]>data[i*step+j]) tmp[2]=1;
	//	else tmp[2]=0;
	//	if (data[(i+1)*step+j]>data[i*step+j]) tmp[3]=1;
	//	else tmp[3]=0;
	//	if (data[(i+1)*step+(j+1)]>data[i*step+j]) tmp[4]=1;
	//	else tmp[4]=0;
	//	if(data[i*step+(j+1)]>data[i*step+j]) tmp[5]=1;
	//	else tmp[5]=0;
	//	if(data[(i-1)*step+(j+1)]>data[i*step+j]) tmp[6]=1;
	//	else tmp[6]=0;
	//	if(data[(i-1)*step+j]>data[i*step+j]) tmp[7]=1;
	//	else tmp[7]=0;	
	//	//计算LBP编码
	//	s.val[0]=(tmp[0]*1+tmp[1]*2+tmp[2]*4+tmp[3]*8+tmp[4]*16+tmp[5]*32+tmp[6]*64+tmp[7]*128);
	//	
	//	cvSet2D(dst, 0, k, s);//写入LBP图像
	//}
}
