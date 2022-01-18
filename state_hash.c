#include "state_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Kreiraj hash tablicu država
 *
 * @return alociranu hash tablicu
 */
StateHashTableP stateHashTable_create()
{
    int i = 0;
    StateHashTableP stateHashTable = NULL;

    stateHashTable = malloc(sizeof(StateHashTable));

    if (!stateHashTable)
    {
        perror("Error creating State hash table");
        return NULL;
    }

    for (i = 0; i < STATE_HASH_TABLE_SIZE; i++)
    {
        stateList_initializeNode(&stateHashTable->table[i], NULL);
    }

    return stateHashTable;
}

/**
 * Unesi èvor države u neku od vezanih lista unutar hash tablice
 *
 * @param stateHashTable hash tablica
 * @param stateNode èvor države
 * @return EXIT_SUCCESS
 */
int stateHashTable_insertStateNode(StateHashTableP stateHashTable, StateListP stateNode)
{
    int i = state_hashFunction(stateNode->state) % STATE_HASH_TABLE_SIZE;

    return stateList_insertSorted(&stateHashTable->table[i], stateNode);
}

/**
 * Isprintaj sve države i gradove iz hash tablice
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
int stateHashTable_print(StateHashTableP stateHashTable)
{
    int i = 0;

    for (i = 0; i < STATE_HASH_TABLE_SIZE; i++)
    {
        stateList_print(&stateHashTable->table[i]);
    }

    return EXIT_SUCCESS;
}

/**
 * Pronaði državu unutar hash tablice
 *
 * @param stateHashTable hash tablica
 * @param stateToFind drzava za pronac
 * @return cvor države iz neke od vezanih lista ako postoji, u suprotnom NULL
 */
StateListP stateHashTable_findStateNode(StateHashTableP stateHashTable, char* stateToFind)
{
    int i = state_hashFunctionFromString(stateToFind) % STATE_HASH_TABLE_SIZE;

    return stateList_findByName(&stateHashTable->table[i], stateToFind);
}

/**
 * Pobriši cijelu hash tablicu, ukljuèujuæi sve vezane liste država i stabala gradova unutar njih
 *
 * @param stateHashTable hash tablica
 * @return EXIT_SUCCESS
 */
int stateHashTable_delete(StateHashTableP stateHashTable)
{
    if (!stateHashTable)
    {
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < STATE_HASH_TABLE_SIZE; i++)
    {
        stateList_deleteAll(&stateHashTable->table[i]);
    }

    free(stateHashTable);
    return EXIT_SUCCESS;
}