#include <iostream>
#include "MatrixOps.h"


int main()
{
	Matrix Mtest1 = Matrix("test1.txt");
	Matrix Mtest2 = Matrix("test2.txt");

	Mtest1.printMatrix();
	Mtest2.printMatrix();
	
	return 0;
}