#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	double **AB, *X;
	int res, n;
	Matrix *A = NULL;
	Matrix *b = NULL;

	int solution_tab[5] = {0};
	double SOL1[4] = {-1., 1., -1., 1.};
	double SOL2[2] = {2., 5.};
	double SOL3[3] = {0.5, 1.5, 0.5};

	//zmienna oznaczająca numer pliku
	int file = 1;
	for (int trial = 0; trial < 5; trial++)
	{

		// if (trial == 4)
		// {
		// 	printf("Przyklad %d\n", trial + 1);
		// 	printf("Do macierzy A wczytuje dane z pliku: %s\n", argv[file]);
		// 	printf("Do macierzy b wczytuje dane z pliku: %s\n", argv[file]);

		// 	printf("Zly format plikow!\n");
		// 	printf("Koniec przykladu %d\n\n\n", trial + 1);
		// 	break;
		// }

		printf("Przyklad %d\n", trial + 1);
		printf("Do macierzy A wczytuje dane z pliku: %s\n", argv[file]);
		A = readFromFile(argv[file++]);
		printf("Do macierzy b wczytuje dane z pliku: %s\n", argv[file]);
		b = readFromFile(argv[file++]);

		if (A == NULL)
		{
			if (trial == 4)
				solution_tab[trial] = 1;
			break;
		}
		if (b == NULL)
			break;

		printToScreen(A);
		printToScreen(b);

		//tworzenie macierzy rozszerzonej A | B -> AB
		// n ->liczba niewiadomych (czyli liczba kolumn, trzeba zadbać o prawidłowe dane)
		//macierz X -> macierz odpowiedzi
		n = A->c;
		AB = (double **)malloc(sizeof(double) * n);
		X = (double *)malloc(sizeof(double) * n);

		if (AB == NULL || X == NULL)
		{
			solution_tab[trial] = 0;
			continue;
		}

		for (int i = 0; i < n; i++)
			AB[i] = (double *)malloc(sizeof(double) * (n + 1));

		for (int i = 0; i < n; i++)
			for (int j = 0; j <= n; j++)
				AB[i][j] = A->data[i][j];

		for (int i = 0; i < n; i++)
			AB[i][n] = b->data[i][0];

		printf("\nAB:\n");
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

			switch (trial)
			{
			case 0:
				for (int j = 0; j < 4; j++)
					if (X[j] == SOL1[j])
						;
					else
					{
						solution_tab[0] = 0;
						continue;
					}
				break;
			case 1:
				for (int j = 0; j < 2; j++)
					if (X[j] == SOL2[j])
						;
					else
					{
						solution_tab[0] = 0;
						continue;
					}
				break;
			case 2:
				for (int j = 0; j < 3; j++)
					if (X[j] == SOL3[j])
						;
					else
					{
						solution_tab[0] = 0;
						continue;
					}
				break;
			default:
				break;
			}

			if (res == 0)
			{
				solution_tab[trial] = 1;

				printf("\nRozwiazanie: \n");
				for (int i = 0; i <= A->r - 1; i++)
				{
					printf("x%d = %lf\n", i + 1, X[i]);
				}
			}
			else if (res == 1)
			{
				fprintf(stderr, "Blad dzielenia przez 0 (element na diagonali = 0)\n");
				solution_tab[trial] = 0;

				if (trial == 3)
					solution_tab[trial] = 1;
			}
		}
		else if (res == 1)
		{
			fprintf(stderr, "Macierz osobliwa dzielenie przez zero!\n");
			solution_tab[trial] = 0;
		}

		printf("Koniec przykladu %d\n\n\n", trial + 1);
		for (int i = 0; i < n + 1; i++)
			free(AB + i);

		free(AB);
		free(X);
	}

	//pokazuje czy test zostal zdany czy nie
	printf("\n\n");
	for (int i = 0; i < 5; i++)
	{
		if (solution_tab[i] == 1)
			printf("Przyklad %d. Zdany test - TAK\n", i + 1);
		else
			printf("Przyklad %d. Zdany test - NIE\n", i + 1);
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
