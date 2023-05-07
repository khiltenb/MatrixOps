#ifndef MATRIXOPS_H_
#define MATRIXOPS_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fcntl.h>

class Matrix
{
private:
	int nC = 0;		// Number of Columns
	int nR = 0;		// Number of Rows
	int * data;		// Matrix Data

public:
	Matrix();
	Matrix(int rows, int columns, int * numbs);
	Matrix(std::string);
	bool changeDims(int rows, int columns);
	bool changeVals(int * numbs);
	bool changeMatrix(int rows, int columns, int * numbs);
	bool ConformCheck(Matrix& rval);
	bool Mcheck(Matrix& rval);
	bool isEmpty();
	Matrix operator=(Matrix& rval);
	bool operator==(Matrix& rval);
	Matrix operator+(Matrix& rval);
	Matrix operator-(Matrix& rval);
	void printMatrix();
};

#endif /* MATRIXOPS_H_ */