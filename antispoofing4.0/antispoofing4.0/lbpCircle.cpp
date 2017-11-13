#include "lbpCircle.h"

void calcLBPH(IplImage *pImg, CvMat* pLBPH)
{

	int i,j,k,p;
	CvMat* pImg_mat = cvCreateMat(pImg->height,pImg->width,CV_32FC1);
	cvConvert(pImg,pImg_mat);
	CvMat * pLBP_mat = cvCreateMat(pImg->height-4,pImg->width-4,CV_32FC1);
	if(pImg->nChannels != 1)//图像必须为单通道
	{
	//	AfxMessageBox("The channels of images must be 1!");
	}
	//LBP图像像素灰度值清零
	for(i=0; i<pLBP_mat->height; i++)
	{
		for(j=0; j<pLBP_mat->width; j++)
		{
			cvmSet(pLBP_mat, i, j, 0);
		}
	}

    int weight[8]; //八个周边像素的权值
	weight[0] = 1;
	for(i=1;i<8;i++) 
		weight[i] = 2 * weight[i-1];

	//为每个像素计算LBP编码
	int height = pImg->height;
	int width = pImg->width;


	double temp[4][2] = {-chaZ,chaZ,-chaZ,-chaZ,chaZ,-chaZ,chaZ,chaZ};
	double temp_y[4] = {0},temp_x[4] = {0};
	int temp_Iy[4] = {0},temp_Ix[4] = {0};
	double dis_y[4] = {0},dis_x[4] = {0};
	double wei[4][4] = {0};
	double end[4] = {0};

	for(i=2,k=0; i<height-2; i++,k++)
	{
		for(j=2,p=0; j<width-2; j++,p++)
		{
			//插值准备
			for(int m = 0;m<4;m++)
			{
				temp_y[m] = temp[m][0]+i;//插值点坐标
				temp_x[m] = temp[m][1]+j;
				temp_Iy[m] = (int)temp_y[m];
				temp_Ix[m] = (int)temp_x[m];
				dis_y[m] = temp_y[m]-temp_Iy[m];
				dis_x[m] = temp_x[m]-temp_Ix[m];
				wei[m][0] =(1-dis_x[m])*(1-dis_y[m]);
				wei[m][1] =dis_x[m]*(1-dis_y[m]);
				wei[m][2] =(1-dis_x[m])*dis_y[m];
				wei[m][3] =dis_x[m]*dis_y[m];
			}
			//插值赋值
			for(int n = 0;n<4;n++)
			{
				switch(n)
				{
				case 0:
					end[n] = (cvmGet(pImg_mat,i-2,j+1)*wei[n][0]+cvmGet(pImg_mat,i-2,j+2)*wei[n][1]+
						cvmGet(pImg_mat,i-1,j+1)*wei[n][2]+cvmGet(pImg_mat,i-1,j+2)*wei[n][3]);
					break;
				case 1:
					end[n] = (cvmGet(pImg_mat,i-2,j-2)*wei[n][0]+cvmGet(pImg_mat,i-2,j-1)*wei[n][1]+
						cvmGet(pImg_mat,i-1,j-2)*wei[n][2]+cvmGet(pImg_mat,i-1,j-1)*wei[n][3]);
					break;
				case 2:
					end[n] = (cvmGet(pImg_mat,i+1,j-2)*wei[n][0]+cvmGet(pImg_mat,i+1,j-1)*wei[n][1]+
						cvmGet(pImg_mat,i+2,j-2)*wei[n][2]+cvmGet(pImg_mat,i+2,j-1)*wei[n][3]);
					break;
				case 3:
					end[n] = (cvmGet(pImg_mat,i+1,j+1)*wei[n][0]+cvmGet(pImg_mat,i+1,j+2)*wei[n][1]+
						cvmGet(pImg_mat,i+2,j+1)*wei[n][2]+cvmGet(pImg_mat,i+2,j+2)*wei[n][3]);
					break;
				}
			}
			if(cvmGet(pImg_mat,i,j+2) >= cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[0]);
			}
			if(end[0] >= (double)cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[1]);
			}
			if(cvmGet(pImg_mat,i-2,j) >= cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[2]);
			}
			if(end[1] >= (double)cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[3]);
			}
			if(cvmGet(pImg_mat,i,j-2) >= cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[4]);
			}
			if(end[2] >= (double)cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[5]);
			}
			if(cvmGet(pImg_mat,i+2,j) >= cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[6]);
			}
			if(end[3] >= (double)cvmGet(pImg_mat, i, j))
			{
				cvmSet(pLBP_mat,k, p,cvmGet(pLBP_mat,k,p)+ weight[7]);
			}
		}
	}
   // hist_num_make(pLBP_mat,pLBPH);
	cvReleaseMat(&pLBP_mat);
}
