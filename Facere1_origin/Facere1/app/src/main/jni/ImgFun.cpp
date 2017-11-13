//#include <com_facere1_code_facere1_MainActivity.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include  <opencv/cv.h>
//#include  <opencv/highgui.h>
//#include  <opencv/cxcore.h>
//#include <opencv/ml.h>
//#include <fstream>
//const int nbrOfTrn = 80;
//const int dimOfFtr = 59;
//
//#include <android/log.h>
//
//#ifndef LOG_TAG
//#define LOG_TAG "ANDROID_LAB"
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
//#endif
//
//
//int	getHopCount(int i) ;
//void lbp59table(uchar *table) ;
//void uniformLBP(IplImage *src,int *result);
//float svm(char* trainfile, int *test);
//float mainProc(char *picPath, char *txtPath);
//using namespace cv;
//using namespace std;
//
//extern "C" {
//JNIEXPORT jfloat JNICALL Java_com_facere1_code_facere1_MainActivity_ImgFun
//    (JNIEnv *, jclass, jstring, jstring);
//
//JNIEXPORT jfloat JNICALL Java_com_facere1_code_facere1_MainActivity_ImgFun(
//    JNIEnv* env, jclass obj, jstring buf, jstring buf1) {
//     const char* str;
//     const char* str1;
//       str = env->GetStringUTFChars(buf, false);
//       str1 = env->GetStringUTFChars(buf1, false);
////     LOGD("########## i = %s", str);
//     LOGE("路径 %s", str);
//    float fret = mainProc((char*)str, (char*)str1);
//     LOGE("返回值 %f", fret);
//
//env->ReleaseStringUTFChars(buf, str);
//env->ReleaseStringUTFChars(buf1, str1);
//     return fret;
//    }
//    }
//
//    //计算跳变次数
//    int	getHopCount(int i)
//    {
//        int a[8] = {0};
//        int cnt = 0;
//        int k = 7;
//        while(i)
//        {
//            a[k] = i&1;
//            i = i >> 1;
//            --k;
//        }
//        for(k = 0; k < 7; k++)
//        {
//            if(a[k] != a[k+1])
//            {
//                ++cnt;
//            }
//        }
//        if(a[0] != a[7])
//        {
//            ++cnt;
//        }
//        return cnt;
//    }
//
//    // 降维数组 由256->59
//    void lbp59table(uchar *table)
//    {
//        memset(table, 0, 256);
//        uchar temp = 1;
//        for(int i = 0; i < 256; i++)
//        {
//            if(getHopCount(i) <= 2)    // 跳变次数<=2 的为非0值
//            {
//                table[i] = temp;
//                temp ++;
//            }
//        }
//    }
//
//    void uniformLBP(IplImage *src,int *result)
//    {
//    	uchar table[256];
//        lbp59table(table);
//
//    	int tmp[8]={0};
//    	int t;
//
//
//    	uchar *data=(uchar*)src->imageData;
//    	int step=src->widthStep;
//
//    	for (int i = 0;i < 59;i++)
//    		result[i] = 0;
//
//    	//周围8个像素点比中间点像素值大(或者相等)的记为1，小的记为0，这样就得到二值图，然后按顺时针方向得到二进制串
//    	for (int i = 1;i < src->height-1;i ++)
//    		for(int j = 1;j < src->width-1;j ++)
//    		{
//    			if(data[(i-1)*step+j-1]>data[i*step+j]) tmp[0]=1;
//    			else tmp[0]=0;
//    			if(data[i*step+(j-1)]>data[i*step+j]) tmp[1]=1;
//    			else tmp[1]=0;
//    			if (data[(i+1)*step+(j-1)]>data[i*step+j]) tmp[2]=1;
//    			else tmp[2]=0;
//    			if (data[(i+1)*step+j]>data[i*step+j]) tmp[3]=1;
//    			else tmp[3]=0;
//    			if (data[(i+1)*step+(j+1)]>data[i*step+j]) tmp[4]=1;
//    			else tmp[4]=0;
//    			if(data[i*step+(j+1)]>data[i*step+j]) tmp[5]=1;
//    			else tmp[5]=0;
//    			if(data[(i-1)*step+(j+1)]>data[i*step+j]) tmp[6]=1;
//    			else tmp[6]=0;
//    			if(data[(i-1)*step+j]>data[i*step+j]) tmp[7]=1;
//    			else tmp[7]=0;
//    			//计算LBP编码，参看http://blog.csdn.net/pi9nc/article/details/18623971
//    			t=(tmp[0]*1+tmp[1]*2+tmp[2]*4+tmp[3]*8+tmp[4]*16+tmp[5]*32+tmp[6]*64+tmp[7]*128);
//
//    			result[(int)table[t]] ++;
//    		}
//    }
//
//    float svm(char* trainfile, int *test)
//
//    {
//
//    		//SVM：
//    		// step 1:
//    		//训练数据的分类标记，即4类
//    		float labels[nbrOfTrn] = {};
//    		for (int i = 0; i < nbrOfTrn; i++)
//    		{
//    			if (i % 4 == 0 || i % 4 == 3)
//    				labels[i] = 1.0;
//    			else
//    				labels[i] = -1.0;
//    		}
//    		CvMat labelsMat = cvMat(nbrOfTrn, 1, CV_32FC1, labels);
//    		//训练数据矩阵
//    		float trainingData[nbrOfTrn][dimOfFtr] = {};
//    		//读取“test_set.txt”文件里记录的特征值。
//    		//这个特征值的提取办法就是灰度化，然后uniformlbp，图片库太大了，为了便于改成app，我这里仅保留已经读取的数据。
//    		fstream trainingfile;
//    		trainingfile.open(trainfile);
//    		for (int i = 0; i < nbrOfTrn; i++)
//    		for (int j = 0; j < dimOfFtr; j++)
//    		{
//    			int tmp;
//    			trainingfile >> tmp;
//    			trainingData[i][j] = (float)tmp;
//    		}
//    		trainingfile.close();
//    		//获得训练矩阵
//    		CvMat trainingDataMat = cvMat(nbrOfTrn, dimOfFtr, CV_32FC1, trainingData);
//
//    		// step 2:
//    		//训练参数设定
//    		CvSVMParams params;
//    		params.svm_type = CvSVM::C_SVC;
//    		//SVM类型
//    		params.kernel_type = CvSVM::LINEAR;             //核函数的类型
//
//    		//SVM训练过程的终止条件, max_iter:最大迭代次数  epsilon:结果的精确性
//    		int k = 10;
//    		params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, k * 100, FLT_EPSILON);
//
//    		// step 3:
//    		//启动训练过程
//    		CvSVM SVM;
//    		SVM.train(&trainingDataMat, &labelsMat, NULL, NULL, params);
//
//    		//讲读入的需要判断的图片的特征值 在这里存为一个数组，然后转为矩阵格式
//    		float sample_data[dimOfFtr] = {};
//    		for (int i = 0; i < dimOfFtr; i++){
//    			sample_data[i] = (float)* (test+i);
//    		}
//    		CvMat sampleDataMat = cvMat(1, dimOfFtr, CV_32FC1, sample_data);
//
//    		//判断图片是否为真人，真人则输出1，照片则输入-1
//    		float response = SVM.predict(&sampleDataMat);
//    		return response;
//    }
//
//    float mainProc(char *picPath, char *txtPath)
//    {
//    	IplImage* face = cvLoadImage(picPath, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
//
//    	//先分配灰度图的空间，把载入图像转换为灰度图
//    	IplImage* Gray_face = cvCreateImage(cvSize(face->width, face->height), face->depth, 1);
//    	cvCvtColor(face, Gray_face, CV_BGR2GRAY);
//
//    	//将256位的灰度图转为59位的二值化直方图，利用uniformlbp这个函数。
//    	int result[59];
//    	uniformLBP(Gray_face, result);
//
//    	//机器学习，判断。判断的输出值是response： 正1代表是人脸，-1代表是照片。
//    	//这里记得改路径，读的文件就是training_set.txt，里面记录了已经提取的特征值。
//    	float response = svm(txtPath,result);
//
//    	cvReleaseImage(&Gray_face);
//    	cvReleaseImage(&face);
//
//    	return response;
//    }
//
