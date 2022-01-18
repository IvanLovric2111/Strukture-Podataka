#define _CRT_SECURE_NO_WARNINGS
#include "state.h"
#include "helpers.h"
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_STATE_ARGUMENTS (2)
#define NUMBER_OF_CHARACTERS_TO_COUNT_FOR_HASH (5)

/**
 * Izraèunaj hash od države
 *
 * @param state idržava
 * @return pozitivan cijeli broj
 */
int state_hashFunction(State* state)
{
    if (!state)
    {
        return 0;
    }

    return state_hashFunctionFromString(state->name);
}

/**
 * Izraèunaj hash od imena države
 *
 * @param stateName ime države
 * @return pozitivan cijeli broj
 */
int state_hashFunctionFromString(char* stateName)
{
    int i = 0;
    int hashCode = 0;
    int n = 0;

    // naziv države može bit i manji od 5 znakova, recimo Èad
    n = min(strlen(stateName), NUMBER_OF_CHARACTERS_TO_COUNT_FOR_HASH);

    for (i = 0; i < n; ++i)
    {
        hashCode += stateName[i];
    }

    return hashCode;
}

/**
 * Stvori državu
 *
 * @param stateName naziv države
 * @param stateFileName ime datoteke u kojoj se nalaze gradovi
 * @return alocirana država
 */
State* state_create(char* stateName, char* stateFileName)
{
    State* state = NULL;

    state = malloc(sizeof(State));
    if (!state)
    {
        perror("State not allocated!\r\n");
        return NULL;
    }

    strcpy(state->name, stateName);
    strcpy(state->fileName, stateFileName);

    return state;
}