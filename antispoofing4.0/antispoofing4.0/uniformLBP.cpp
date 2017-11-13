 //计算跳变次数  
#include "uniformLBP.h"

int	getHopCount(int i)  
{  
    int a[8] = {0};  
    int cnt = 0;  
    int k = 7;  
    while(i)  
    {  
        a[k] = i&1;  
        i = i >> 1;  
        --k;  
    }  
    for(k = 0; k < 7; k++)  
    {  
        if(a[k] != a[k+1])  
        {  
            ++cnt;  
        }  
    }  
    if(a[0] != a[7])  
    {  
        ++cnt;  
    }  
    return cnt;  
}  
  
// 降维数组 由256->59  
void lbp59table(uchar *table)  
{  
    memset(table, 0, 256);  
    uchar temp = 1;  
    for(int i = 0; i < 256; i++)  
    {  
        if(getHopCount(i) <= 2)    // 跳变次数<=2 的为非0值  
        {  
            table[i] = temp;  
            temp ++;  
        }  
    }  
}  
  
void uniformLBP(IplImage *src,int *result)
{
	uchar table[256];  
    lbp59table(table);

	int tmp[8]={0};
	int t;
	CvScalar s;

	//IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);
	uchar *data=(uchar*)src->imageData;
	int step=src->widthStep;

	//int result[59];
	for (int i = 0;i < 59;i++)
		result[i] = 0;

	for (int i = 1;i < src->height-1;i ++)
		for(int j = 1;j < src->width-1;j ++)
		{
			if(data[(i-1)*step+j-1]>data[i*step+j]) tmp[0]=1;
			else tmp[0]=0;
			if(data[i*step+(j-1)]>data[i*step+j]) tmp[1]=1;
			else tmp[1]=0;
			if (data[(i+1)*step+(j-1)]>data[i*step+j]) tmp[2]=1;
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
			t=(tmp[0]*1+tmp[1]*2+tmp[2]*4+tmp[3]*8+tmp[4]*16+tmp[5]*32+tmp[6]*64+tmp[7]*128);
			
			result[(int)table[t]] ++;
			//cvSet2D(temp, i, j, s);//写入LBP图像
		}
	
	/*for (int i = 0;i < 59;i++)
	{
		cout << i << ' ' << result[i] << endl;
	}*/

	/*for (int i = 0;i < 59;i++)
	{
		CvScalar s;
		s.val[0] = result[i];
		cvSet2D(dst,0,i,s);
	}*/
}
//void uniformLBP(Mat &image, Mat &result, uchar *table)  
//{  
//	uchar table[256];  
//    lbp59table(table); 
//    for(int y = 1; y < image.rows-1; y ++)  
//    {  
//        for(int x = 1; x < image.cols-1; x++)  
//        {  
//            uchar neighbor[8] = {0};  
//            neighbor[0] = image.at<uchar>(y-1, x-1);  
//            neighbor[1] = image.at<uchar>(y-1, x);  
//            neighbor[2] = image.at<uchar>(y-1, x+1);  
//            neighbor[3] = image.at<uchar>(y, x+1);  
//            neighbor[4] = image.at<uchar>(y+1, x+1);  
//            neighbor[5] = image.at<uchar>(y+1, x);  
//            neighbor[6] = image.at<uchar>(y+1, x-1);  
//            neighbor[7] = image.at<uchar>(y, x-1);  
//            uchar center = image.at<uchar>(y, x);  
//            uchar temp = 0;  
//            for(int k = 0; k < 8; k++)  
//            {  
//                temp += (neighbor[k] >= center)* (1<<k);  // 计算LBP的值  
//            }  
//            result.at<uchar>(y,x) = table[temp];   //  降为59维空间  
//        }  
//    }  
//}  
  
//int main()  
//{  
//    
//    Mat image = imread("F:\\lena.png", 0);  
//    if(!image.data)  
//    {  
//        cout << "Fail to load image" << endl;  
//        return 0;  
//    }  
//    Mat result;  
//    result.create(Size(image.cols, image.rows), image.type());  
//    uniformLBP(image, result, table);  
//  
//    namedWindow("uniformResult", 0);  
//    imshow("uniformResult", result);  
//  
//    waitKey(0);  
//    return 0;  
//      
//}  