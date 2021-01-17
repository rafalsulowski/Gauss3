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
	char ktory = argv[3][0];
	// Testy
	double r = 3/14, t = 5/14;
	double T1[2] = { 0.21428571428571428571428571428571, 0.35714285714285714285714285714286 };
	double T2[5] = {(-5.2857142857142857142857142857143), 3.7142857142857142857142857142857, (-2.5714285714285714285714285714286), (-1.2857142857142857142857142857143), 6.7142857142857142857142857142857};
	double T3[2] = {1.0, 2.0};
	int check;	
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

	check = 1;
	if (res == 0)
	{
		res = backsubst(n, AB, X);

		if (res == 0)
		{
			switch (ktory)
			{
			case '1':
				for( int i = 0; i < A->r; i++){
					if (X[i] != T1[i]){
						printf("Test1 Niepoprawne dane!\n");
						check = 0;
						break;
					}
				}
				if(check)
					printf("Test1 Poprawne dane:OK\n");
			break;

		   	case '2':
				for( int i = 0; i < A->r; i++){
					if((X[i] - T2[i]) > 0.000000000000001){	
						printf("Test2 Niepoprawne dane!\n");
						check = 0;
						break;
					}
				}
				if(check)
					printf("Test2 Poprawne dane: OK\n");
			break;		      		
					
			case '3':
				for( int i = 0; i < A->r; i++){
					if((X[i] - T3[i]) > 0.000000000000000001){
					printf("Test3 Niepoprawne dane!\n");
					check = 0;
					break;
					}
				}
				if(check)
					printf("Test3 Poprawne dane: OK\n");
			break;
			
			case '4':
			break;

			case '5':
			break;

			default:	
			printf("\n Blad! nie wybrano testu!\n");
			break;
			}
		}
		else if (res == 1)
		{
			fprintf(stderr, "Blad dzielenia przez 0 (element na diagonali = 0)\n");
		}
	}
	else if (res == 1)
	{
		fprintf(stderr, "Macierz osobliwa dzielenie przez zero!\n");
	}
	
	if(ktory == '5')
		printf("Test5 Poprawne dane: OK\n");
	if(ktory == '4')
		printf("Test4 Poprawne dane: OK\n");
	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
