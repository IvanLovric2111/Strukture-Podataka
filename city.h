#pragma once

#define MAX_CITY_NAME (256)

typedef struct _city
{
    char name[MAX_CITY_NAME];
    int population;
} City;

/**
 * Usporedi dva grada po sljedeæim kriterijima:
 * 1. populacija, zatim
 * 2. naziv ako je populacija gradova ista
 *
 * @param city1 prvi grad
 * @param city2 drugi grad
 * @return manje od nula ako je city1 < city2, nula ako su city1 == city2, više od nula ako je city1 > city2
 */
int city_compare(City* city1, City* city2);

/**
 * Stvori grad
 *
 * @param name naziv grada
 * @param population populacija grada
 * @return alociran grad
 */
City* city_create(char* name, int population);