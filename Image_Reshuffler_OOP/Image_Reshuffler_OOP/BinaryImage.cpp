#include "BinaryImage.h"

#pragma region Constructors

//default constructor
BinaryImage::BinaryImage()
{
	_R = 1;
	_C = 1;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = 0;
}

//constructor to store an image elements of which can take values 0 and 1 only
BinaryImage::BinaryImage(int sizeR, int sizeC, double* input_data, double threshold)
{
	_R = sizeR;
	_C = sizeC;
	_threshold = threshold;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = input_data[i] > threshold ? 1 : 0;
}

//copy constructor
BinaryImage::BinaryImage(const BinaryImage& old)
{
	_R = old._R;
	_C = old._C;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = old._data[i];
}

BinaryImage::BinaryImage(Matrix& old, double threshold)
{
	_R = old.getR();
	_C = old.getC();
	_threshold = threshold;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		_data[i] = old.getData()[i] > _threshold ? 1 : 0;
}

#pragma endregion

#pragma region Operator Overloads

BinaryImage BinaryImage::operator-(const BinaryImage& other)
{
	BinaryImage temp = createNew(other);

	for (int x = 0; x < (temp._R * temp._C); x++)
	{
		if (other._data[x] != this->_data[x])
			temp._data[x] = 1;
		else
			temp._data[x] = 0;
	}

	return temp;
}

BinaryImage BinaryImage::operator=(const BinaryImage& other)
{
	delete[] _data;
	_R = other._R;
	_C = other._C;

	_data = new double[_R * _C];

	for (int i = 0; i < (_R * _C); i++)
		this->_data[i] = other._data[i];

	return *this;
}

BinaryImage BinaryImage::operator*(const BinaryImage& other)
{
	BinaryImage temp = createNew(other);

	for (int x = 0; x < (temp._R * temp._C); x++)
	{
		temp._data[x] = this->_data[x] * other._data[x];
	}

	return temp;
}

#pragma endregion

#pragma region Helpers

BinaryImage BinaryImage::createNew(const BinaryImage& other)
{
	BinaryImage temp;
	temp._R = other._R;
	temp._C = other._C;

	temp._data = new double[temp._R*temp._C];

	return temp;
}

#pragma endregion 