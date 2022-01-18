#pragma once

#include "city.h"

struct _cityTree;
typedef struct _cityTree* CityTreeP;
typedef struct _cityTree
{
    City* city;
    CityTreeP left;
    CityTreeP right;
} CityTree;

/**
 * Kreira cvor i inicijalizira atribute
 *
 * @param cityName ime grada
 * @param population populacija grada
 * @return CityTreeP - alocirana memorija
 */
CityTreeP cityTree_createNode(char* cityName, int population);

/**
 * Unosi cvor rekurzivno u stablo
 *
 * @param current trenutni cvor rekurzije
 * @param cityNode cvor koji se unosi
 * @return cvor koji se unosi ako je trenutni cvor prazan, u suprotnom trenutni cvor
 */
CityTreeP cityTree_insert(CityTreeP current, CityTreeP cityNode);

/**
 * Brise samo cvor
 *
 * @param cityNode cvor koji se brise
 * @return EXIT_SUCCESS
 */
int cityTree_freeNode(CityTreeP cityNode);

/**
 * Rekurzivno brise cijelo stablo
 *
 * @param current trenutni cvor
 * @return NULL
 */
CityTreeP cityTree_delete(CityTreeP current);

/**
 * Rekurzivno ispisuje cijelo stablo od najveceg prema najmanjem gradu
 *
 * @param current trenutni cvor
 * @return EXIT_SUCCESS
 */
int cityTree_print(CityTreeP current);

/**
 * Rekurzivno ispisuje cijelo stablo od najveceg prema najmanjem gradu
 * ako je parametar veæi od parametra 'population'
 *
 * @param current trenutni cvor
 * @param population populacija grada iznad kojeg ispisujemo
 * @return EXIT_SUCCESS
 */
int cityTree_printBiggerThan(CityTreeP current, int population);
