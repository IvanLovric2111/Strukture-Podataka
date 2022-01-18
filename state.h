#pragma once

#include <stdio.h>

#define MAX_STATE_NAME (256)

typedef struct _state
{
    char name[MAX_STATE_NAME];
    char fileName[FILENAME_MAX];
} State;

/**
 * Izraèunaj hash od države
 *
 * @param state idržava
 * @return pozitivan cijeli broj
 */
int state_hashFunction(State* state);

/**
 * Izraèunaj hash od imena države
 *
 * @param stateName ime države
 * @return pozitivan cijeli broj
 */
int state_hashFunctionFromString(char* stateName);

/**
 * Stvori državu
 *
 * @param stateName naziv države
 * @param stateFileName ime datoteke u kojoj se nalaze gradovi
 * @return alocirana država
 */
State* state_create(char* stateName, char* stateFileName);