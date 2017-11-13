#include "fft.h"

void dft(complex<double>*Data,int length,int flag)
{
	//cout<< "lalla";
    int i,j;
    complex<double> wn;
    complex<double> temp[9];
    for(i=0;i<length;i++)
   {
        temp[i]=0;
        for(j=0;j<length;j++)
       {
            wn=complex<double>(cos(2.0*pi/length*i*j),sin(flag*2.0*pi/length*i*j));
            temp[i]+=Data[j]*wn;    
        }           
    }
    if(flag==1)
        for(i=0;i<length;i++)
            Data[i] = complex<double>(temp[i].real(), -temp[i].imag());
  // delete[] temp;
}  

//void main()
//{
//	complex<double> data[4];
//	for (int i = 0;i < 4;i++)
//	{
//		double re,im;
//		cin >> re >> im;
//		data[i] = complex<double>(re,im);
//	}
//	dft(data,2,1);
//	cout << "hahahah"<< endl;
//	double test = data[0].real();
//	if (test > 0) cout << "Yeah!"<< endl;
//}