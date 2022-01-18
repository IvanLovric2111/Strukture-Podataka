#pragma once

#include <stdio.h>

#define MAX_STATE_NAME (256)

typedef struct _state
{
    char name[MAX_STATE_NAME];
    char fileName[FILENAME_MAX];
} State;

/**
 * Izra�unaj hash od dr�ave
 *
 * @param state idr�ava
 * @return pozitivan cijeli broj
 */
int state_hashFunction(State* state);

/**
 * Izra�unaj hash od imena dr�ave
 *
 * @param stateName ime dr�ave
 * @return pozitivan cijeli broj
 */
int state_hashFunctionFromString(char* stateName);

/**
 * Stvori dr�avu
 *
 * @param stateName naziv dr�ave
 * @param stateFileName ime datoteke u kojoj se nalaze gradovi
 * @return alocirana dr�ava
 */
State* state_create(char* stateName, char* stateFileName);