#include <math.h>
#include <iostream>
#include <complex>

const double pi = 3.14159265358979323846;
using namespace std;

void dft(complex<double>*Data,int Log2N,int flag)
{
	cout<< "lalla";
    int i,j,length;
    complex<double> wn;
    length = 1<<Log2N;
    complex<double>* temp = new complex<double>(length);
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
            Data[i] = complex<double>(temp[i].real(), temp[i].imag());
   // delete[] temp;
}  

