#include <iostream>
#include <iomanip>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef MATRIXOPS_H_
#define MATRIXOPS_H_

class Matrix
{
private:
	int nC = 0;		// Number of Columns
	int nR = 0;		// Number of Rows
	double * data;		// Matrix Data

public:
	Matrix();
	Matrix(std::string fileName);
	bool changeDims(int rows, int columns);
	bool changeVals(double * numbs);
	bool changeMatrix(int rows, int columns, double * numbs);
	bool ConformCheck(Matrix& rval);
	bool Mcheck(Matrix& rval);
	// bool SaveMatrix(std::string fileName);
	bool isEmpty();
	// Matrix operator=(Matrix& rval);
	bool operator==(Matrix& rval);
	Matrix operator+(Matrix& rval);
	Matrix operator-(Matrix& rval);
	Matrix operator*(Matrix& rval);
	void printMatrix();
};

#endif /* MATRIXOPS_H_ */