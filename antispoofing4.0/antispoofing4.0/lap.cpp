#include "fft.h"
#include "lap.h"

const float sin_chart[9] = {0.6427876,0.9848078,0.8660254,0.3420201,-0.3420201,-0.8660254,-0.9848076,-0.6427876,0};
const float cos_chart[9] = {0.7660444,0.1736482,-0.5000000,-0.9396926,-0.9396926,-0.5000000,0.1736482,0.7660444,1};

const int dx[9] = {0,0,0,0,-1,-1,-1,-1,0};
const int dy[9] = {0,0,-1,-1,-1,-1,0,0,0};

void LAP(IplImage *src, int *result)
{  
	//int t;
	//CvScalar s;

	//IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U,1);
	uchar *data=(uchar*)src->imageData;
	int step=src->widthStep;

	//int result[59];
	//for (int i = 0;i < 59;i++)
	//	result[i] = 0;
	for (int i = 0;i < 256;i++)
		result[i] = 0;

	for (int i = 1;i < src->height-1;i += 5)
		for(int j = 1;j < src->width-1;j += 5)
		{
			//cout << i << ' ' << j << endl;
			
			double tmp[9];
			//bilinear(src, i, j, tmp);

			//双线性插值法
			for (int k = 0;k < 9;k ++)
			{
				int x1 = i + dx[k];
				int y1 = j + dy[k];
				int x2 = x1 + 1;
				int y2 = y1 + 1;
				double cx = i + sin_chart[k];
				double cy = j + cos_chart[k];
				/*if ((cx == 100)&&(cy == 100)) cout << x1 << ' ' << y1 << "-->" << x2 << ' ' << y2 << endl;
				if ((cx == 100)&&(cy == 100)) cout << (int)data[x1 * step + y1] << ' ' 
					 << (int)data[x2 * step + y1] << ' '
					 << (int)data[x1 * step + y2] << ' '
					 << (int)data[x2 * step + y2] << ' '<<endl;*/
				tmp[k] = double(data[x1 * step + y1]) * (x2 - cx) * (y2 - cy) +
						 double(data[x1 * step + y2]) * (x2 - cx) * (cy - y1) +
						 double(data[x2 * step + y1]) * (cx - x1) * (y2 - cy) +
						 double(data[x2 * step + y2]) * (cx - x1) * (cy - y1);
				//if ((cx == 100)&&(cy == 100)) cout << "tmp:" << tmp <<endl;
				//if ((cx == 100)&&(cy == 100)) cout << (int)result[i] << endl;
				
			}

			//离散傅立叶变换
			complex<double> p[9];
			for (int k = 0;k < 9;k ++)
				p[k] = complex<double>(tmp[k],0.0);
			dft(p,9,1);

			//转化为8位二进制数
			int b[8]={0};
			for (int k = 4;k > 0;k --)
			{
				double real = p[k].real();
				if (abs(real) < 0.00000001) real = 0;
				if (real >= 0) b[8 - 2 * k] = 1; 
				else b[8 - 2 * k] = 0;
				double imag = p[k].imag();
				if (abs(imag) < 0.00000001) imag = 0;
				if (imag >= 0) b[8 - 2 * k + 1] = 1; 
				else b[8 - 2 * k + 1] = 0;
			}
			int val = b[7] * 128 + b[6] * 64 + b[5] * 32 + b[4] * 16 + b[3] * 8 + b[2] * 4 + b[1] * 2 + b[0];
			//cout << "val: " << val << endl;
			//cout << "ooooooo~"<<endl;
			result[val]++;
			//cout << "ooooooo~"<<endl;
		}
}
	