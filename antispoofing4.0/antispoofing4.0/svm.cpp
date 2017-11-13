#include "svm.h"

void svm(char* trainfile, char *testfile)
{  
	for (int k = 10;k < 11;k ++)
	{
		//SVM：
		// step 1:  
		//训练数据的分类标记，即4类  
		float labels[nbrOfTrn] = {};
		for (int i = 0;i < nbrOfTrn; i++)
		{
			if (i % 4 == 0 || i % 4 == 3) 
				labels[i] = 1.0;
			else 
				labels[i] = -1.0;
		}
		CvMat labelsMat = cvMat(nbrOfTrn, 1, CV_32FC1, labels);  
		//训练数据矩阵  
		float trainingData[nbrOfTrn][dimOfFtr] = {};
		fstream trainingfile;
		trainingfile.open(trainfile);
		for (int i = 0;i < nbrOfTrn;i ++)
			for (int j = 0;j < dimOfFtr;j ++)
			{
				float tmp;
				trainingfile >> tmp;
				trainingData[i][j] = tmp;
			}
	
		trainingfile.close();

		CvMat trainingDataMat = cvMat(nbrOfTrn, dimOfFtr, CV_32FC1, trainingData);  
  
		// step 2:  
		//训练参数设定  
		CvSVMParams params;  
		params.svm_type = CvSVM::C_SVC;          
		   //SVM类型  
		params.kernel_type = CvSVM::LINEAR;             //核函数的类型  

		//SVM训练过程的终止条件, max_iter:最大迭代次数  epsilon:结果的精确性
		params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, k * 100, FLT_EPSILON );  
  
		// step 3:  
		//启动训练过程  
		CvSVM SVM;  
		SVM.train( &trainingDataMat, &labelsMat, NULL,NULL, params);  

		int nbrOfError = 0;

		float sample_data[nbrOfTst][dimOfFtr] = {};
		trainingfile.open(testfile);
		for (int i = 0;i < nbrOfTst;i ++)
			for (int j = 0;j < dimOfFtr;j ++)
			{
				float tmp;
				trainingfile >> tmp;
				sample_data[i][j] = tmp;
			}

		for (int i = 0;i < nbrOfTst;i ++)
		{
			//CvMat sampleMat;
			CvMat sampleDataMat = cvMat(1, dimOfFtr, CV_32FC1, sample_data[i]); 
			float response = SVM.predict(&sampleDataMat);
			//cout << "Test " << i + 1 << " : " << response <<endl;
			if ((i % 4 == 0 || i % 4 == 3)&&(response == -1.0)) 
				nbrOfError ++;
			if ((i % 4 == 1 || i % 4 == 2)&&(response == 1.0)) 
				nbrOfError ++;
		}
		float errorRate =  (float)(nbrOfError) / (nbrOfTst);
		cout << "Times of iteration: "<< k << "  Error rate: "<< errorRate * 100 << "%" << endl;
	}
	
}