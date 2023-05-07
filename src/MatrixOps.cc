#include "MatrixOps.h"

	/**
	 * @brief Construct a new Matrix:: Matrix object
	 * This is a simple matrix constructor that when invoked, will produce an empty matrix, initializing nC (number of columns) and nR (number of Rows) to zero.
	 * 
	 */
	Matrix::Matrix()
	{
		nC = 0;
		nR = 0;
	}

	/**
	 * @brief Construct a new Matrix:: Matrix object initialized to given parameters
	 * This function is meant to take in matrix dimensions and an array of matrix elements to initialize the Matrix object
	 * 
	 * @param rows Number of rows
	 * @param columns Number of columns
	 * @param numbs data array of size rows * columns that houses the matrix data
	 */
	Matrix::Matrix(int rows, int columns, int * numbs)
	{
		nC = columns;
		nR = rows;
		data = numbs;
	}


	/**
	 * @brief Construct a new Matrix:: Matrix object from a text file
	 * 
	 */
	Matrix::Matrix(std::string)
	{
		int fd;
		int bytesRead;
		char * buf = new char[1024];
	}
	


	/**
	 * @brief Reconstruct the matrix with new dimensions, but keep the data where possible. Fill in the new data sections with 0s.
	 * 
	 * @param rows 
	 * @param columns 
	 * @return true 
	 * @return false 
	 */
	bool Matrix::changeDims(int rows, int columns)
	{
		if (rows == nR && columns == nC)	// require that new dims be different than old dims
		{
			return false;
		}

		int * temp = new int[columns * rows];						// initiate a new string of numbers to be pointed to.
		if (nC <= columns && nR <= rows)							// if the new dimensions are larger than the old ones,
		{
			for (int i = 0; i < nR; ++i)								// for each row of the old
			{
				for (int j = 0; j < nC; ++j)								// for each position in that row
				{
					temp[i * columns  + j] = data[i * nC + j];					// copy the data from that position to the new data string
				}
			}
		}
		else if (nC >= columns && nR <= rows)						// if the new columns is smaller, but new rows is larger,
		{
			for (int i = 0; i < nR; ++i)								// for each row of the old
			{
				for (int j = 0; j < columns; ++j)							// for each position in that row
				{
					temp[i * columns  + j] = data[i * nC + j];					// copy the data from that position to the new data string
				}
			}
		}
		else if (nC <= columns && nR >= rows)						// if the new columns is larger, but new rows is smaller,
		{
			for (int i = 0; i < rows; ++i)								// for each row of the old
			{
				for (int j = 0; j < nC; ++j)								// for each position in that row
				{
					temp[i * columns  + j] = data[i * nC + j];					// copy the data from that position to the new data string
				}
			}
		}
		else														// if new dims are smaller than old dims
		{
			for (int i = 0; i < rows; ++i)								// for each row of the old
			{
				for (int j = 0; j < columns; ++j)							// for each position in that row
				{
					temp[i * columns  + j] = data[i * nC + j];					// copy the data from that position to the new data string
				}
			}
		}
		nC = columns;		// set class-recognized columns to new number
		nR = rows;			// set class-recognized rows to new number
		return true;		// return success
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

	bool Matrix::isEmpty()
	{
		if (nC == 0 || nR == 0 || data == nullptr)
		{
			return true;
		}
		else
		{
			return false;
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

	void Matrix::printMatrix()
	{
		if (this->isEmpty())
		{
			std::cout << "This matrix is empty." << std::endl;
		}
		else
		{
			std::cout << std::endl << std::endl;
			for (int i = 0; i < this->nR; ++i)
			{
				for (int j = 0; j < this->nC; ++j)
				{
					std::cout << data[this->nR * i + j] << " ";
				}
				std::cout << std::endl;
			}
		}
	}