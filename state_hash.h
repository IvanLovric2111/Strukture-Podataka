#pragma once

#include "state_list.h"

#define STATE_HASH_TABLE_SIZE (11)

struct _stateHashTable;
typedef struct _stateHashTable* StateHashTableP;
typedef struct _stateHashTable
{
    StateList table[STATE_HASH_TABLE_SIZE];
} StateHashTable;

/**
 * Kreiraj hash tablicu dr�ava
 *
 * @return alociranu hash tablicu
 */
StateHashTableP stateHashTable_create();

/**
 * Unesi �vor dr�ave u neku od vezanih lista unutar hash tablice
 *
 * @param stateHashTable hash tablica
 * @param stateNode �vor dr�ave
 * @return EXIT_SUCCESS
 */
int stateHashTable_insertStateNode(StateHashTableP stateHashTable, StateListP stateNode);

/**
 * Isprintaj sve dr�ave i gradove iz hash tablice
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
int stateHashTable_print(StateHashTableP stateHashTable);

/**
 * Prona�i dr�avu unutar hash tablice
 *
 * @param stateHashTable hash tablica
 * @param stateToFind drzava za pronac
 * @return cvor dr�ave iz neke od vezanih lista ako postoji, u suprotnom NULL
 */
StateListP stateHashTable_findStateNode(StateHashTableP stateHashTable, char* stateToFind);

/**
 * Pobri�i cijelu hash tablicu, uklju�uju�i sve vezane liste dr�ava i stabala gradova unutar njih
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
int stateHashTable_delete(StateHashTableP stateHashTable);
