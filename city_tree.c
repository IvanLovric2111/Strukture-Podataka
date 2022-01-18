#include "city_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Kreira cvor i inicijalizira atribute
 *
 * @param cityName ime grada
 * @param population populacija grada
 * @return CityTreeP - alocirana memorija
 */
CityTreeP cityTree_createNode(char* cityName, int population)
{
    CityTreeP cityNode = NULL;
    City* city = NULL;

    city = city_create(cityName, population);

    if (!city)
    {
        return NULL;
    }

    cityNode = malloc(sizeof(CityTree));

    if (!cityNode)
    {
        perror("City node not allocated!");
        free(city);
        return NULL;
    }

    cityNode->city = city;
    cityNode->left = NULL;
    cityNode->right = NULL;

    return cityNode;
}

/**
 * Unosi cvor rekurzivno u stablo
 *
 * @param current trenutni cvor rekurzije
 * @param cityNode cvor koji se unosi
 * @return cvor koji se unosi ako je trenutni cvor prazan, u suprotnom trenutni cvor
 */
CityTreeP cityTree_insert(CityTreeP current, CityTreeP cityNode)
{
    int result = 0;

    if (!current)
    {
        return cityNode;
    }

    result = city_compare(current->city, cityNode->city);

    if (result < 0)
    {
        current->right = cityTree_insert(current->right, cityNode);
    }
    else if (result > 0)
    {
        current->left = cityTree_insert(current->left, cityNode);
    }
    else
    {
        printf("City %s with population %d already exists!\r\n", cityNode->city->name, cityNode->city->population);
        cityTree_freeNode(cityNode);
    }

    return current;
}

/**
 * Brise samo cvor
 *
 * @param cityNode cvor koji se brise
 * @return EXIT_SUCCESS
 */
int cityTree_freeNode(CityTreeP cityNode)
{
    if (!cityNode)
    {
        return EXIT_SUCCESS;
    }

    if (cityNode->city)
    {
        free(cityNode->city);
        cityNode->city = NULL;
    }

    free(cityNode);
    return EXIT_SUCCESS;
}

/**
 * Rekurzivno brise cijelo stablo
 *
 * @param current trenutni cvor
 * @return NULL
 */
CityTreeP cityTree_delete(CityTreeP current)
{
    if (!current)
    {
        return NULL;
    }

    current->left = cityTree_delete(current->left);
    current->right = cityTree_delete(current->right);
    cityTree_freeNode(current);
    return NULL;
}

/**
 * Rekurzivno ispisuje cijelo stablo od najveceg prema najmanjem gradu
 *
 * @param current trenutni cvor
 * @return EXIT_SUCCESS
 */
int cityTree_print(CityTreeP current)
{
    if (!current)
    {
        return EXIT_SUCCESS;
    }

    cityTree_print(current->right);
    printf("\t%s %d\r\n", current->city->name, current->city->population);
    cityTree_print(current->left);
    return EXIT_SUCCESS;
}

/**
 * Rekurzivno ispisuje cijelo stablo od najveceg prema najmanjem gradu
 * ako je parametar veæi od parametra 'population'
 *
 * @param current trenutni cvor
 * @param population populacija grada iznad kojeg ispisujemo
 * @return EXIT_SUCCESS
 */
int cityTree_printBiggerThan(CityTreeP current, int population)
{
    if (!current)
    {
        return EXIT_SUCCESS;
    }

    cityTree_printBiggerThan(current->right, population);
    if (current->city->population > population)
    {
        printf("\t%s %d\r\n", current->city->name, current->city->population);
    }
    cityTree_printBiggerThan(current->left, population);
    return EXIT_SUCCESS;
}