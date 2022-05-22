#include"Vectorr.h"
#include"Matrix.h"
#include<iostream>
int main()
{
	TMatrix<int> A(1000,1000,-3);
	TMatrix<int> B(1000, 1000, 3);
	A + B;
	
	

	return 0;
}

