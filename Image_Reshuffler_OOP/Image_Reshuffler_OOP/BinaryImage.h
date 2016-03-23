#pragma once
#include "Matrix.h"

class BinaryImage : public Matrix
{

public:
	//default constructor
	BinaryImage();
	//constructor to store an image
	//elements of which can take values 0 and 1 only
	BinaryImage(int sizeR, int sizeC, double* input_data, double threshold);
	//copy constructor 
	BinaryImage(const BinaryImage& old);
	//Matrix Constructor
	BinaryImage(Matrix& old, double threshold);

	//Operator Overloads
	BinaryImage operator-(const BinaryImage& other);
	BinaryImage operator*(const BinaryImage& other);
	BinaryImage operator=(const BinaryImage& other);

	//Helpers
	BinaryImage createNew(const BinaryImage& other);
};

