#pragma once
#include <iostream>

using namespace std;

class Matrix
{
public:
	//default constructor 
	Matrix();
	//Constructor to create Matrix for specified size 
	Matrix(int sizeR, int sizeC, double* val);
	//Copy Constructor (for when Matrix = Matrix)
	Matrix(const Matrix& old);
	//deconstructor
	~Matrix();

	//Get/Set
	const double get(int i, int j);
	Matrix getBlock(int startRow, int endRow, int startCol, int endCol);

	void set(int i, int j, double val);
	void setBlock(int startRow, int startCol, Matrix& m);

	int getR();
	int getC();
	double* getData();

	//helpers
	void print();
	Matrix createNew(const Matrix& other);
	int getSum();

	//Invoke all the operators overloads
	Matrix operator=(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);

protected:
	int _R, _C;
	double *_data;
	double _threshold;
};