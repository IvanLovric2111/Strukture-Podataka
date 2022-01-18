#pragma once

#include "state.h"
#include "city_tree.h"

struct _stateList;
typedef struct _stateList* StateListP;
typedef struct _stateList
{
    State* state;
    StateListP next;
    CityTreeP cityRoot;
} StateList;

/**
 * Kreiraj èvor prema argumentima
 *
 * @param stateName naziv drzave
 * @param stateFileName naziv datoteke drzave
 * @return alociran èvor
 */
StateListP stateList_createNodeWithArgs(char* stateName, char* stateFileName);

/**
 * Kreiraj èvor
 *
 * @param state informacije o državi
 * @return èvor države
 */
StateListP stateList_create(State* state);

/**
 * Inicijaliziraj èvor
 *
 * @param stateNode èvor kojeg treba inicijalizirat
 * @param state informacije o državi
 * @return EXIT_SUCCESS
 */
int stateList_initializeNode(StateListP stateNode, State* state);

/**
 * Uveži èvor nakon èvora
 *
 * @param position pozicija nakon koje uvezujemo èvor
 * @param stateNode èvor kojeg treba uvezati
 * @return EXIT_SUCCESS
 */
int stateList_insertAfter(StateListP position, StateListP stateNode);

/**
 * Uveži èvor unutar vezane liste
 *
 * @param head glava vezane liste
 * @param stateNode èvor kojeg treba uvezat
 * @return EXIT_SUCCESS
 */
int stateList_insertSorted(StateListP head, StateListP stateNode);

/**
 * Pobriši èvor i sve gradove unutar njega
 *
 * @param stateNode èvor kojeg treba pobrisat
 * @return EXIT_SUCCESS
 */
int stateList_freeNode(StateListP stateNode);

/**
 * Pobriši èvor nakon èvora i sve gradove unutar tog èvora
 *
 * @param position pozicija èvor prije onog kojeg želimo pobrisat
 * @return EXIT_SUCCESS
 */
int stateList_deleteNodeAfter(StateListP position);

/**
 * Pobriši cijelu listu i sve gradove u njima
 *
 * @param head glava vezane liste
 * @return EXIT_SUCCESS
 */
int stateList_deleteAll(StateListP head);

/**
 * Ispiši iz liste sve države i njegove gradove
 *
 * @param head glava vezane liste
 * @return EXIT_SUCCESS
 */
int stateList_print(StateListP head);

/**
 * Pronaði državu iz liste po imenu
 *
 * @param head glava vezane liste
 * @param name ime države koju tražimo
 * @return adresu èvora ako je pronaðen, u suprotnom NULL
 */
StateListP stateList_findByName(StateListP head, char* name);