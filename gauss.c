#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(int n, double **AB)
{
	int i, j, k;
  double m;

  // eliminacja współczynników

  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (fabs(AB[i][i]) < 1e-12)
        return 1;

      m = -AB[j][i] / AB[i][i];

      for (k = i + 1; k <= n; k++)
        AB[j][k] += m * AB[i][k];
    }
  }

  return 0;
}
