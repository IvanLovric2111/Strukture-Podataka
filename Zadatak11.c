#define _CRT_SECURE_NO_WARNINGS
#include "zadatak11.h"
#include "state_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX (1024)

// ********************** Privatne funkcije, vidljive samo unutar ove datoteke, zato ih oznaèavamo sa 'static'

/**
 * Proèitaj gradove iz datoteke
 *
 * @param stateFile datoteka s gradovima
 * @return root stabla
 */
static CityTreeP readCitiesFromFile(char* stateFile);

/**
 * Proèitaj države skupa s gradovima iz datoteke
 *
 * @param stateHashTable hash tablica u koju se èita sve
 * @param statesFile datoteka s državama
 * @return EXIT_SUCCESS ako je sve ok, u suprotnom EXIT_FAILURE
 */
static int readStatesFromFile(StateHashTableP stateHashTable, char* statesFile);

/**
 * Izvrši upit nad hash tablicom
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
static int stateQuery(StateHashTableP stateHashTable);

/**
 * Zadatak 11
 *
 * @return EXIT_SUCCESS ako je uspilo, u suprotnom EXIT_FAILURE
 */
int zadatak11()
{
	StateHashTableP stateHashTable = NULL;
	FILE* fp = NULL;
	int status = 0;
	char fileName[FILENAME_MAX] = { 0 };

	stateHashTable = stateHashTable_create();

	if (!stateHashTable)
	{
		return EXIT_FAILURE;
	}

	printf("Please, insert filename -> ");
	scanf(" %s", fileName);
	status = readStatesFromFile(stateHashTable, fileName);

	if (status != EXIT_SUCCESS)
	{
		printf("Failed to read file %s!\r\n", fileName);
		return EXIT_FAILURE;
	}

	stateHashTable_print(stateHashTable);
	stateQuery(stateHashTable);
	stateHashTable_delete(stateHashTable);

	return EXIT_SUCCESS;
}

/**
 * Proèitaj gradove iz datoteke
 *
 * @param stateFile datoteka s gradovima
 * @return root stabla
 */
static CityTreeP readCitiesFromFile(char* stateFile)
{
	CityTreeP root = NULL;
	FILE* fp = NULL;
	char cityName[MAX_CITY_NAME] = { 0 };
	int cityPopulation = 0;

	fp = fopen(stateFile, "r");

	if (!fp)
	{
		perror("File not opened!\r\n");
		return NULL;
	}

	while (!feof(fp))
	{
		CityTreeP city = NULL;
		fscanf(fp, " %s %d", cityName, &cityPopulation);
		city = cityTree_createNode(cityName, cityPopulation);

		if (!city)
		{
			root = cityTree_delete(root);
			return NULL;
		}

		root = cityTree_insert(root, city);
	}

	fclose(fp);
	return root;
}

/**
 * Proèitaj države skupa s gradovima iz datoteke
 *
 * @param stateHashTable hash tablica u koju se èita sve
 * @param statesFile datoteka s državama
 * @return EXIT_SUCCESS ako je sve ok, u suprotnom EXIT_FAILURE
 */
static int readStatesFromFile(StateHashTableP stateHashTable, char* statesFile)
{
	FILE* fp = NULL;
	char statesName[MAX_STATE_NAME] = { 0 };
	char statesFileName[FILENAME_MAX] = { 0 };

	fp = fopen(statesFile, "r");

	if (!fp)
	{
		perror("File not opened!\r\n");
		return EXIT_FAILURE;
	}

	while (!feof(fp))
	{
		StateListP stateNode = NULL;
		fscanf(fp, " %s %s", statesName, statesFileName);
		stateNode = stateList_createNodeWithArgs(statesName, statesFileName);

		if (!stateNode)
		{
			stateHashTable_delete(stateHashTable);
			return EXIT_FAILURE;
		}

		stateNode->cityRoot = readCitiesFromFile(stateNode->state->fileName);
		stateHashTable_insertStateNode(stateHashTable, stateNode);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

/**
 * Izvrši upit nad hash tablicom
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
static int stateQuery(StateHashTableP stateHashTable)
{
	char stateToFind[MAX_STATE_NAME] = { 0 };
	int populationMin = 0;
	StateListP state = NULL;

	while (true)
	{
		printf("Insert state to find -> ");
		scanf(" %s", stateToFind);

		state = stateHashTable_findStateNode(stateHashTable, stateToFind);

		if (!state)
		{
			printf("State %s not found, please try again!\r\n", stateToFind);
		}
		else
		{
			break;
		}
	}

	printf("Insert minimal city population to print -> ");
	scanf(" %d", &populationMin);

	cityTree_printBiggerThan(state->cityRoot, populationMin);
	return EXIT_SUCCESS;
}