#include "Matrix.h"

#pragma region Constructors/Deconstructor

//default constructor 
Matrix::Matrix()
{
	_R = 1;
	_C = 1;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = 0;
}

//Constructor to create Matrix for specified size 
Matrix::Matrix(int sizeR, int sizeC, double* val)
{
	_R = sizeR;
	_C = sizeC;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = val[i];
}

//Copy Constructor (for when Matrix = Matrix)
Matrix::Matrix(const Matrix& old)
{
	_R = old._R;
	_C = old._C;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = old._data[i];
}

//deconstructor
Matrix::~Matrix()
{
	delete[] _data;
}

#pragma endregion

#pragma region Get/Set

const double Matrix::get(int i, int j)
{
	return _data[(i * _C) + j];
}

Matrix Matrix::getBlock(int startRow, int endRow, int startCol, int endCol)
{
	int R = (endRow - startRow) + 1;
	int C = (endCol - startCol) + 1;
	int count = 0;

	double *temp = new double[R * C];

	for (int i = startRow; i < (R + startRow); i++)
	{
		for (int j = startCol; j < (C + startCol); j++)
			temp[count++] = get(i, j);
	}

	Matrix mTemp = Matrix(C, R, temp);
	delete temp;
	return mTemp;
}

void Matrix::set(int i, int j, double val)
{
	_data[(i * _C) + j] = val;
}

//set block
void Matrix::setBlock(int startRow, int startCol, Matrix& old)
{
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
			_data[(startRow + i) * _C + startCol + j] = old.get(i, j);
	}
}

//functions - Get Rows and Get Columns (For BinaryImage)
int Matrix::getR()
{
	return _R;
}

int Matrix::getC()
{
	return _C;
}

double* Matrix::getData()
{
	return _data;
}

#pragma endregion

#pragma region Helpers (Print and createNew)

void Matrix::print()
{
	for (int i = 0; i < (_R * _C); i++)
	{
		cout << _data[i] << " ";
		if ((i + 1) % _C == 0) cout << endl;
	}
}

Matrix Matrix::createNew(const Matrix& other)
{
	Matrix temp;
	temp._R = other._R;
	temp._C = other._C;

	temp._data = new double[temp._R*temp._C];

	return temp;
}

int Matrix::getSum()
{
	int sum = 0;

	for (int i = 0; i < (_R * _C); i++)
		sum += _data[i];

	return sum;
}

#pragma endregion 

#pragma region Operator Overloads

Matrix Matrix::operator=(const Matrix& other)
{
	delete[] _data;
	_R = other._R;
	_C = other._C;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
	{
		this->_data[i] = other._data[i];
	}

	return *this;
}

Matrix Matrix::operator-(const Matrix& other)
{
	Matrix temp = createNew(other);

	for (int x = 0; x < (temp._R*temp._C); x++)
	{
		temp._data[x] = this->_data[x] - other._data[x];
	}

	return temp;
}

Matrix Matrix::operator*(const Matrix& other)
{
	Matrix temp = createNew(other);

	for (int x = 0; x < (temp._R * temp._C); x++)
	{
		temp._data[x] = this->_data[x] * other._data[x];
	}

	return temp;
}

#pragma endregion