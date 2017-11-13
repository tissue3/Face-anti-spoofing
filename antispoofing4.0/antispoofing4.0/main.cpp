#include <opencv2/opencv.hpp>
#include <cv.h> 
#include <highgui.h>
#include <cxcore.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>

#include "main.h"
#include "lap.h"
#include "svm.h"
#include "fileoption.h"

using namespace std;
using namespace cv;

const int feature[9] = {6,57,69,122,133,186,198,249,255};

int main(int argc, char* argv[])
{	
	//计算训练样本的lbp
	cout << "training..."<<endl;
	ofstream outputfile;
	outputfile.open("E:\\train_release\\training_set.txt");
	outputfile.close();
	for (int i = 0;i < nbrOfTrn;i ++)
	{
		stringstream tmp;
		tmp << "E:\\train_release\\" << i + 33 << ".jpg";
		
		string filename = tmp.str(); 
		IplImage* face = cvLoadImage(filename.data(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
		 
		IplImage* Gray_face = cvCreateImage( cvSize( face->width, face->height), face->depth, 1);//先分配图像空间
		cvCvtColor(face, Gray_face ,CV_BGR2GRAY);//把载入图像转换为灰度图
		
		int result[dimOfFtr];
		LAP(Gray_face,result);

		/*float resultf[dimOfFtr];
		normalize(result, resultf, dimOfFtr);*/

		cout << i << endl;
		write_to_file(result, dimOfFtr, "E:\\train_release\\training_set.txt");
	}

	cout << "choosing..."<<endl;
	//随机选取测试样本
	bool testBool[120];
	int testSet[nbrOfTst];
	for (int i = 0;i < 120;i ++) testBool[i] = false;
	for (int i = 0;i < nbrOfTst / 4;i ++)
	{
		srand( (unsigned)time(NULL));
		int tmp = rand()%30;
		while (testBool[tmp])
		{
			srand((unsigned)time(NULL));
			tmp = rand()%30;
		}
		testBool[tmp] = true;
		cout << tmp << endl;
		testSet[i * 4] = tmp * 4;
		testSet[i * 4 + 1] = tmp * 4 + 1;
		testSet[i * 4 + 2] = tmp * 4 + 2;
		testSet[i * 4 + 3] = tmp * 4 + 3;
	}

	cout << "testing..."<<endl;
	//计算测试样本的lbp
	outputfile.open("E:\\test_release\\test_set.txt");
	//outputfile << (int)data[i] << ' ';
	outputfile.close();

	//int error;
	for (int i = 0;i < nbrOfTst;i ++)
	{
		cout << i << endl;
		stringstream tmp;
		tmp << "E:\\test_release\\" << testSet[i] + 1 << ".jpg";
		
		string filename = tmp.str(); 
		IplImage* face = cvLoadImage(filename.data(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

		IplImage* Gray_face = cvCreateImage( cvSize( face->width, face->height ), face->depth, 1);//先分配图像空间
		cvCvtColor(face, Gray_face ,CV_BGR2GRAY);//把载入图像转换为灰度图
		//IplImage* lbp_face =   cvCreateImage(cvSize(lbpWidth, lbpHeight), IPL_DEPTH_8U,1);//先分配图像空间

		int result[dimOfFtr];
		LAP(Gray_face,result);

		//float resultf[dimOfFtr];
		//normalize(result, resultf, dimOfFtr);

		write_to_file(result, dimOfFtr, "E:\\test_release\\test_set.txt");
	}

	//cout << error / nbrOfTst<<endl;
	svm("E:\\train_release\\training_set.txt","E:\\test_release\\test_set.txt");
	system("pause");  
	return 0;

}