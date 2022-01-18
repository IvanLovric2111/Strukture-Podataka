#define _CRT_SECURE_NO_WARNINGS
#include "city.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CITY_ARGUMENTS (2)

/**
 * Usporedi dva grada po sljedeæim kriterijima:
 * 1. populacija, zatim
 * 2. naziv ako je populacija gradova ista
 *
 * @param city1 prvi grad
 * @param city2 drugi grad
 * @return manje od nula ako je city1 < city2, nula ako su city1 == city2, više od nula ako je city1 > city2
 */
int city_compare(City* city1, City* city2)
{
    int result = city1->population - city2->population;

    if (result == 0)
    {
        result = strcmp(city1->name, city2->name);
    }

    return result;
}

/**
 * Stvori grad
 *
 * @param name naziv grada
 * @param population populacija grada
 * @return alociran grad
 */
City* city_create(char* name, int population)
{
    City* city = NULL;

    city = malloc(sizeof(City));

    if (!city)
    {
        perror("City failed to allocate!");
        return NULL;
    }

    strcpy(city->name, name);
    city->population = population;

    return city;
}