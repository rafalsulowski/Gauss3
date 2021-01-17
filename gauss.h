#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"
#include <stdbool.h>
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(int n, double **AB);

#endif
