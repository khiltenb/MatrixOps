#include "MatrixOps.h"

	// ease of use functions
	int findPos(char delim, char * buf, int start, int limit)
	{
		while (buf[start] != delim && start <= limit + 1)
		{
			start++;
		}

		if (start > limit)
		{
			return -1;
		}
		else
		{
			return start;
		}
	}


	// Class functions

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
	 * @brief Construct a new Matrix:: Matrix object from a txt file
	 * This constructor takes in a text file that is assumed to be formatted such that the number of columns and rows are listed on the first line, followed by 
	 * 		the data that makes up the matrix with each subsequent line being a row that forms the matrix. It will be assumed that missing element at the end of 
	 * 		the row is a zero.
	 * 
	 * @param fileName - name of file to be used in 
	 * 
	 */
	Matrix::Matrix(std::string fileName)
	{
		//	variables for looping/parsing through input
		int fd;
		int start = 0;
		int end = 0;
		int row = 0;
		int col = 0;
		int tempChecker = 0;
		int bytesRead;
		char * buf = new char[4096];
		bool loop = true;

		fd = open(fileName.c_str(), O_RDONLY);
		if (fd < 0)
		{
			std::cout << "File not found." << std::endl;
			nR = 0;
			nC = 0;
			data = nullptr;
			return;
		}
		
		// get num of rows
		bytesRead = read(fd, buf, 4096);
		end = findPos(' ', buf, end, bytesRead);
		char * tempBuf = new char[end - start];
		memcpy(tempBuf, &buf[start], end - start);
		nR = std::stof(tempBuf);
		delete[] tempBuf;
		start = end;
		end++;


		// get num of columns
		end = findPos('\n', buf, end, bytesRead);
		tempBuf = new char[end-start];
		memcpy(tempBuf, &buf[start], end - start);
		nC = std::stof(tempBuf);
		delete[] tempBuf;
		start = end;
		end++;

		data = new double[nR * nC];

		// loop through input and set up data member
		while (bytesRead == 4096 || loop)
		{
			if (loop == true)
			{
				loop = false;
			}
			int endOfLine = 0;
			while ((endOfLine = findPos('\n', buf, end, bytesRead)) != -1 && row <= nR)
			{
				end = findPos(' ', buf, end, bytesRead);
				while (col < nC  && row < nR && end < endOfLine)
				{
					tempBuf = new char[end - start];
					memcpy(tempBuf, &buf[start], end - start);
					data[row * nC + col] = std::stof(tempBuf);
					delete[] tempBuf;
					col++;
					start = end + 1;
					end = findPos(' ', buf, start, bytesRead);
				}

				if (end > endOfLine)
				{
					tempBuf = new char[end - endOfLine];
					memcpy(tempBuf, &buf[start], end - endOfLine);
					data[row * nC + col] = std::stof(tempBuf);
					delete[] tempBuf;
					col++;
					for (int i = col; i < nC; ++i)
					{
						data[row * nC + i] = 0.0;
					}
					start = endOfLine;
					col = 0;
					row++;
				}
				else
				{
					col = 0;
					row++;
				}

				tempChecker = endOfLine;
			}

			if (endOfLine == -1)
			{
				start = 0;
				int endOfBufferSz = bytesRead - tempChecker;
				end = 0;
				char * tempBuf2 = new char[endOfBufferSz];
				memcpy(tempBuf2, &buf[tempChecker + 1], endOfBufferSz - 1);
				bytesRead = read(fd, buf, 4096);

				if (bytesRead != 0)
				{
					endOfLine = findPos('\n', buf, 0, bytesRead);
					end = findPos(' ', tempBuf2, end, bytesRead);
					while (col < nC && end != -1)
					{
						tempBuf = new char[end - start];
						memcpy(tempBuf, &tempBuf2[start], end - start);
						data[row * nR + col] = std::stof(tempBuf2);
						delete[] tempBuf;
						col++;
						start = end + 1;
						end = findPos(' ', tempBuf2, end, bytesRead);
					}

					end = findPos(' ', buf, 0, bytesRead);
					tempBuf = new char[tempChecker - start + end];
					memcpy(&tempBuf[0], &tempBuf2[start], tempChecker - start);
					memcpy(&tempBuf[0], &buf[0], end);
					data[nC * row + col] = std::stof(tempBuf);
					delete[] tempBuf;
					col++;
					start = end;

					//
					while (col < nC && end < endOfLine)
					{
						tempBuf = new char[end - start];
						memcpy(tempBuf, &buf[start], end - start);
						data[row * nC + col] = std::stof(tempBuf2);
						delete[] tempBuf;
						col++;
						start = end;
						end = findPos(' ', buf, end, bytesRead);
					}

					if (end > endOfLine)
					{
						tempBuf = new char[end - endOfLine];
						memcpy(tempBuf, &buf[start], end - endOfLine);
						data[row * nC + col] = std::stof(tempBuf);
						delete[] tempBuf;
						col++;
						for (int i = col; i < nC; ++i)
						{
							data[row * nR + i] = 0.0;
						}
						col = 0;
						row++;
					}
					else
					{
						col = 0;
						row++;
					}
					delete[] tempBuf2;
				}
				else
				{
					end = findPos(' ', tempBuf2, 0, endOfBufferSz);
					while (col < nC && end != -1)
					{
						tempBuf = new char[endOfBufferSz];
						memcpy(tempBuf, &tempBuf2[start], end - start);
						data[row * nR + col] = std::stof(tempBuf);
						delete[] tempBuf;
						col++;
						start = end + 1;
						end = findPos(' ', tempBuf2, start, endOfBufferSz);
					}
					tempBuf = new char[endOfBufferSz - start];
					memcpy(tempBuf, &tempBuf2[start], endOfBufferSz - start);
					data[row * nC + col] = std::stof(tempBuf);
				}
			}
			else
			{
				bytesRead = read(fd, buf, 4096);
			}

			
			start = 0;
			end = 0;
		}
		delete[] tempBuf;
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

		double * temp = new double[columns * rows];						// initiate a new string of numbers to be pointed to.
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
	
	bool Matrix::changeVals(double * numbs)
	{
		data = numbs;
		return true;
	}

	bool Matrix::changeMatrix(int rows, int columns, double * numbs)
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

	// bool Matrix::SaveMatrix(std::string fileName)
	// {
	// 	//
	// }

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
	
	// Matrix Matrix::operator=(Matrix& rval)
	// {
	// 	this->nC = rval.nC;
	// 	this->nR = rval.nR;
	// 	this->data = new double[nR*nC];
	// 	for (int i = 0; i < nR*nC; ++i)
	// 	{
	// 		data[i] = rval.data[i];
	// 	}
	// 	return *this;
	// }

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


	// Matrix Matrix::operator*(Matrix& rval)
	// {
	// 	if (Mcheck(rval))
	// 	{
	// 		//
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Matrices cannot be multiplied. Dimensions do not match up." << std::endl;
	// 		return Matrix();
	// 	}
	// }


	Matrix Matrix::operator*(double rval)
	{
		for (int i = 0; i < nC * nR; ++i)
		{
			this->data[i] *= rval;
		}
		return *this;
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

