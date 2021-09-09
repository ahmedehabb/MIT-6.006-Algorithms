#include<iostream>
using namespace std;
#include <iomanip>


// high precision Multiplication 
// x*y (both radix d)
// if (x,y) are n-digit numbers
// so 0 <= x,y < r^n
long double High_Precision_Multiplication(long double  x, long double  y , int d, int n ) {
	//x= x1 * r^n/2 + x0;

	long double  x0 = fmod( x, pow(d,n/2) ); // cant use % for doubles!
	// x2 is lowest significant half of x
	long double  x1 = (x - x0)/ pow(d,n/2) ;
	// x1 is highest significant part 

	long double  y0 = fmod( y, pow(d,n/2) ); // cant use % for doubles!
	// x2 is lowest significant half of x
	long double  y1 = (y - y0)/ pow(d,n/2) ;
	// x1 is highest significant part 

	//if(n/2 > 64)
	//{
	//	High_Precision_Multiplication(x0,y0,d,n/2);
	//	High_Precision_Multiplication(x1,y1,d,n/2);
	//}

	long double  z0 = x0 * y0 ;
	long double  z1 = x0*y1 + x1*y0 ;
	long double  z2 = x1 * y1 ;

	return z2 * pow(d,n) + z1 * pow(d,n/2) + z0 ;
}



int main(){
	double result = 213; 

	


	system("pause");
}