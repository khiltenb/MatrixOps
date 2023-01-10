#ifndef MATRIXOPS_H_
#define MATRIXOPS_H_

class Matrix
{
	int nC = 0;		// Number of Columns
	int nR = 0;		// Number of Rows
	int * data;		// Matrix Data

	Matrix();
	Matrix(int rows, int colums, int * numbs);
	bool changeDims(int rows, int columns);
	bool changeVals(int * numbs);
	bool changeMatrix(int rows, int columns, int * numbs);
	bool ConformCheck(Matrix& rval);
	bool Mcheck(Matrix& rval);
	Matrix operator=(Matrix& rval);
	Matrix operator+(Matrix& rval);
	Matrix operator-(Matrix& rval);
};

#endif /* MATRIXOPS_H_ */