#include "main.h"
#include <iostream>
#include <fstream>

using namespace std;
void main()
{
	fstream trainingfile;
	trainingfile.open("E://test_release//test_set.txt");
	int error1 = 0;
	int error2 = 0;
	for (int i = 0;i < 100;i ++)
		for (int j = 0;j < 256;j ++)
		{
			int tmp;
			trainingfile >> tmp;
			if (j ==255)
			{
				cout << i << ' ' << tmp << endl;
				if ((i%4 == 0)||(i%4 == 3))
					if (tmp > 18000) error1 ++;
				if ((i%4 == 1)||(i%4 == 2))
					if (tmp <= 18000) error2 ++;
			}
		}
	trainingfile.close();
	cout << error1 << ' ' << error2 << endl;
	system("pause");
}