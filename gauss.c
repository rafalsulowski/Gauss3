#include "gauss.h"
/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(int n, double **AB)
{
  int i, j, k;
  double m, tmp;

  // Metoda eliminacju gaussa
  // eliminacja współczynników

  for (k = 0; k < n; k++)
  {
    //Find the best pivot
    int p = k;
    double maxPivot = 0.0;
    for (i = k; i < n; i++)
    {
      if (fabs(AB[i][k] > maxPivot))
      {
        maxPivot = fabs(AB[i][k]);
        p = i;
      }
    }

    // Swap rows k and p
    if (p != k)
    {
      for (i = k; i < n + 1; i++)
      {
        tmp = AB[p][i];
        AB[p][i] = AB[k][i];
        AB[k][i] = tmp;
      }
    }

    // Elimination of variables
    for (i = k + 1; i < n; i++)
    {
      double m = AB[i][k] / AB[k][k];
      for (j = k; j < n + 1; j++)
        AB[i][j] -= m * AB[k][j];
    }
  }

  printf("\n\nAB:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= n; j++)
      printf("%lf ", AB[i][j]);
    printf("\n");
  }

  return 0;
}
