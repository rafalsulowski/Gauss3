#include "gauss.h"
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int
eliminate (int n, double **AB)
{
  int i, j, k;
  double m;

  // eliminacja współczynników
  for (k = 0; k < n; k++)
    {
    // Wybór elementu Głównego dla każdej iteracji (pod-macierzy)
      int p = k;
      double pivot = 0.0;
      for (i = k; i < n; i++)
	{
	  if (fabs(AB[i][k]) > pivot)
	    {
	      pivot = fabs(AB[i][k]);
	      p = i; // który wiersz zamieniamy
	    }
	}

      // Zamiana wierszy
      if (p != k){  
	for(i = k; i < n+1; i++){
		m = AB[p][i];			
		AB[p][i] = AB[k][i];
		AB[k][i] = m;
		}
	}
      // Eliminacja Gaussa
      for (i = k + 1; i < n; i++)
	{
	  m = AB[i][k] / AB[k][k];
	  for (j = k; j < n + 1; j++)
	  	AB[i][j] -= m * AB[k][j];
	}
    }

  /*
     for (i = 0; i < n - 1; i++)
     {
     for (j = i + 1; j < n; j++)
     {
     if (fabs(AB[i][i]) < 1e-12)
     return 1;

     m = AB[j][i] / AB[i][i];

     for (k = 0; k <= n; k++)
     AB[j][k] -= m * AB[i][k];
     }
     }
   */

  return 0;
}
