#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	double **AB, *X;
	int res;
	Matrix *A = readFromFile(argv[1]);
	Matrix *b = readFromFile(argv[2]);
	Matrix *x;

	if (A == NULL)
		return -1;
	if (b == NULL)
		return -2;
	printToScreen(A);
	printToScreen(b);

	//tworzenie macierzy rozszerzonej A | B -> AB
	// n ->liczba niewiadomych (czyli liczba kolumn, trzeba zadbać o prawidłowe dane)
	//macierz X -> macierz odpowiedzi
	int n = A->c;
	AB = (double **)malloc(sizeof(double) * n);
	X = (double *)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++)
		AB[i] = (double *)malloc(sizeof(double) * (n + 1));

	for (int i = 0; i < n; i++)
		for (int j = 0; j <= n; j++)
			AB[i][j] = A->data[i][j];

	for (int i = 0; i < n; i++)
		AB[i][n] = b->data[i][0];

	printf("\n\nAB:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
			printf("%lf ", AB[i][j]);
		printf("\n");
	}

	res = eliminate(n, AB);

	if (res == 0)
	{
		res = backsubst(n, AB, X);

		if (res == 0)
		{
			printf("\nRozwiazanie: \n");
			for (int i = 0; i <= A->r - 1; i++)
				printf("x%d = %lf\n", i + 1, X[i]);
		}
		else if (res == 1)
		{
			fprintf(stderr, "Blad dzielenia przez 0 (element na diagonali = 0)");
		}
	}
	else if (res == 1)
	{
		fprintf(stderr, "Macierz osobliwa dzielenie przez zero!\n");
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
