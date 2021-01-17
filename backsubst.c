#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 */
int backsubst(int n, double **AB, double *X)
{
	double s;
	for (int i = n - 1; i >= 0; i--)
	{
		s = AB[i][n];
		for (int j = n - 1; j >= i + 1; j--)
			s -= AB[i][j] * X[j];
		if (fabs(AB[i][i]) < 1e-12)
			return 1;
		X[i] = s / AB[i][i];
	}
	return 0;
}
