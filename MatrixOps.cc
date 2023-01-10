#include "MatrixOps.h"

	Matrix::Matrix()
	{
		nC = 0;
		nR = 0;
	}

	Matrix::Matrix(int rows, int columns, int * numbs)
	{
		nC = columns;
		nR = rows;
		data = numbs;
	}
	
	bool Matrix::changeDims(int rows, int columns)
	{
		nC = columns;
		nR = rows;
		return true;
	}
	
	bool Matrix::changeVals(int * numbs)
	{
		data = numbs;
		return true;
	}

	bool Matrix::changeMatrix(int rows, int columns, int * numbs)
	{
		return changeDims(rows, columns) && changeVals(numbs);
	}
	
	bool Matrix::ConformCheck(Matrix& rval)
	{
		if (this->nR != rval.nR)
		{
			return false;
		}
		else if (this->nC != rval.nC)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	bool Matrix::Mcheck(Matrix& rval)
	{
		if (this->nC != rval.nR)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	Matrix Matrix::operator=(Matrix& rval)
	{
		this->nC = rval.nC;
		this->nR = rval.nR;
		this->data = new int[nR*nC];
		for (int i = 0; i < nR*nC; ++i)
		{
			data[i] = rval.data[i];
		}
		return *this;
	}

	bool Matrix::operator==(Matrix& rval)
	{
		if (this->nR != rval.nR || this->nC != rval.nC)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < this->nR * this->nC; ++i)
			{
				if (this->data[i] != rval.data[i])
				{
					return false;
				}
			}
			return true;
		}
	}

	Matrix Matrix::operator+(Matrix& rval)
	{
		if (this->ConformCheck(rval))
		{
			for (int i = 0; i < this->nC * this->nR; ++i)
			{
				this->data[i] += rval.data[i];
			}
			return *this;
		}
		else
		{
			// should throw an error here. Class is not set up, so for now returns empty matrix.
			return Matrix();
		}
	}
	
	Matrix Matrix::operator-(Matrix& rval)
	{
		if (this->ConformCheck(rval))
		{
			for (int i = 0; i < this->nC * this->nR; ++i)
			{
				this->data[i] -= rval.data[i];
			}
			return *this;
		}
		else
		{
			// should throw an error here. Class is not set up, so for now returns empty matrix.
			return Matrix();
		}
	}