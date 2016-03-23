#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include "Matrix.h"
#include "BinaryImage.h"

Matrix matrixShuffled;
Matrix matrixNoisey;

double* readTXT(char *fileName, int sizeR, int sizeC);
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);
void swapBlock(int startRowSource, int startColSource, int startRowDest, int startColDest);
void NNS();

int main()
{
	//R = Number of Rows, C = Number of Columns
	int R = 512, C = 512;
	double* shuffled_data = 0;
	double* noisey_data = 0;

	//shuffled logo
	char* shuffledFile = "Data/shuffled_logo.txt";
	shuffled_data = readTXT(shuffledFile, R, C);
	matrixShuffled = Matrix(R, C, shuffled_data);

	//noisy logo
	char* noiseyLogo = "Data/unshuffled_logo_noisy.txt";
	noisey_data = readTXT(noiseyLogo, R, C);
	matrixNoisey = Matrix(R, C, noisey_data);

	NNS();

	shuffled_data = matrixShuffled.getData();

	//ouput Restored Logo
	char* outputFileName = "Data/logo_restored.pgm";
	short int Q = 255;
	WritePGM(outputFileName, shuffled_data, R, C, Q);

	delete[] noisey_data;

	return 0;
}

#pragma region Read Text File
// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}
#pragma endregion 

#pragma region Convert data into PGM
// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR * sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i < sizeR * sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR * sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}
#pragma endregion 

#pragma region Swap Block

//mainR and MainC = Block I want to move and set
//destR and destC = Destination block, block I want to move to
void swapBlock(int mainR, int mainC, int destR, int destC)
{
	Matrix temp = matrixShuffled.getBlock(mainR, mainR + 31, mainC, mainC + 31);
	matrixShuffled.setBlock(mainR, mainC, matrixShuffled.getBlock(destR, destR + 31, destC, destC + 31));
	matrixShuffled.setBlock(destR, destC, temp);
}

#pragma endregion

#pragma region Nearest Neighbour Search (NNS)
void NNS()
{
	//indexs for noisey block
	int xBlock = 0, yBlock = 0;

	//indexs for minimum score (x and y)
	int xMinimum = 0, yMinimum = 0;

	// Minimumn score set
	int minScore = INT_MAX;

	do
	{
		//instantiate Noisey Data
		Matrix noiseyData = matrixNoisey.getBlock(xBlock * 32, xBlock * 32 + 31, yBlock * 32, yBlock * 32 + 31);
		BinaryImage binaryNoisey = BinaryImage(noiseyData, 110);

		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				//get shuffled block
				Matrix shuffledData = matrixShuffled.getBlock(i * 32, i * 32 + 31, j * 32, j * 32 + 31);
				//convert to Binary Image format
				BinaryImage binaryShuffled = BinaryImage(shuffledData, 110) - binaryNoisey;
				//squared difference
				binaryShuffled = binaryShuffled * binaryShuffled;
				//sum squared difference
				int totalSum = binaryShuffled.getSum();

#pragma region Debug Info
				/*cout << "X: " << xBlock << " Y: " << yBlock
				<< ", Shuffled X: " << i << " Y: " << j
				<< ", SUM: " << totalSum << endl;*/
#pragma endregion

				if (totalSum < minScore)
				{
					xMinimum = i;
					yMinimum = j;
					minScore = totalSum;
				}
			}
		}

		swapBlock(xBlock * 32, yBlock * 32, xMinimum * 32, yMinimum * 32);

		//reset variables to allow for next block
		xMinimum = 0;
		yMinimum = 0;
		minScore = INT_MAX;

		//if xBlock (column) is at the end of the 
		if (++xBlock % 16 == 0)
		{
			xBlock = 0;
			yBlock++;
		}
	} while (xBlock != 16 && yBlock != 16);
}

#pragma endregion