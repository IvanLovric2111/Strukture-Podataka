#include "helpers.h"
#include <stdio.h>
#include <ctype.h>

/**
 * Vrati manji broj od dva broja
 *
 * @param a prvi broj
 * @param b drugi broj
 * @return manji broj iz skupa (a, b)
 */
int min(int a, int b)
{
    return a < b ? a : b;
}