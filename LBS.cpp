#include <iostream>
#include <cmath>

int**matrix transpose(int **matrix, int row, int col)
{
	// dynamically allocate an array
	int **result;
	result = new int *[col]; //creates a new array of pointers to int objects
	for (int i = 0; i < col; i++)
	{
		result[i] = new int[row];
	}
	// transposing
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result[j][i] = matrix[i][j];
		}
	}
}

int**matrix Multiply(int **aMatrix,int **bMatrix) {

	int n = sizeof(aMatrix[0]);
	int all1 = sizeof(aMatrix);
	int m = all1 / n;
	int k = sizeof(bMatrix[0]);
	int all2 = sizeof(bMatrix);
	int b = all2 / k;
	if (n != b)
	{
		std::cout << "Matrix dimention does not match";
		std::exit(EXIT_FAILURE);
	}
	int product[m][n];

	for (int row = 0; row < m; row++) {
		for (int col = 0; col < n; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.
			for (int inner = 0; inner < b; inner++) {
				product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];
			}
		}
	}
	return pruduct
}

int main() 
{
	int Vertices_previous[10][4];
	int Vertices_transpose[4][10];
	int scalar[10][4];
	int Translation_compose[4][4];
	//int num_of_frames;
	int i;
	for (i = 0; i < 4; i++)
	{
		Vertices_transpose = transpose(Vertices_previous, 10, 4);
		Rigid = Multiply(scalar, Translation_compose)
		Vertices_previous = Multiply(Rigid, Vertices_transpose);
	}
	return 0;
}