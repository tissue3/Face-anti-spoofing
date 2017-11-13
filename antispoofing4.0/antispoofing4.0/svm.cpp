#include "svm.h"

void svm(char* trainfile, char *testfile)
{  
	for (int k = 10;k < 11;k ++)
	{
		//SVM��
		// step 1:  
		//ѵ�����ݵķ����ǣ���4��  
		float labels[nbrOfTrn] = {};
		for (int i = 0;i < nbrOfTrn; i++)
		{
			if (i % 4 == 0 || i % 4 == 3) 
				labels[i] = 1.0;
			else 
				labels[i] = -1.0;
		}
		CvMat labelsMat = cvMat(nbrOfTrn, 1, CV_32FC1, labels);  
		//ѵ�����ݾ���  
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
		//ѵ�������趨  
		CvSVMParams params;  
		params.svm_type = CvSVM::C_SVC;          
		   //SVM����  
		params.kernel_type = CvSVM::LINEAR;             //�˺���������  

		//SVMѵ�����̵���ֹ����, max_iter:����������  epsilon:����ľ�ȷ��
		params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, k * 100, FLT_EPSILON );  
  
		// step 3:  
		//����ѵ������  
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