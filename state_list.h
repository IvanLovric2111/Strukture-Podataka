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
 * Kreiraj �vor prema argumentima
 *
 * @param stateName naziv drzave
 * @param stateFileName naziv datoteke drzave
 * @return alociran �vor
 */
StateListP stateList_createNodeWithArgs(char* stateName, char* stateFileName);

/**
 * Kreiraj �vor
 *
 * @param state informacije o dr�avi
 * @return �vor dr�ave
 */
StateListP stateList_create(State* state);

/**
 * Inicijaliziraj �vor
 *
 * @param stateNode �vor kojeg treba inicijalizirat
 * @param state informacije o dr�avi
 * @return EXIT_SUCCESS
 */
int stateList_initializeNode(StateListP stateNode, State* state);

/**
 * Uve�i �vor nakon �vora
 *
 * @param position pozicija nakon koje uvezujemo �vor
 * @param stateNode �vor kojeg treba uvezati
 * @return EXIT_SUCCESS
 */
int stateList_insertAfter(StateListP position, StateListP stateNode);

/**
 * Uve�i �vor unutar vezane liste
 *
 * @param head glava vezane liste
 * @param stateNode �vor kojeg treba uvezat
 * @return EXIT_SUCCESS
 */
int stateList_insertSorted(StateListP head, StateListP stateNode);

/**
 * Pobri�i �vor i sve gradove unutar njega
 *
 * @param stateNode �vor kojeg treba pobrisat
 * @return EXIT_SUCCESS
 */
int stateList_freeNode(StateListP stateNode);

/**
 * Pobri�i �vor nakon �vora i sve gradove unutar tog �vora
 *
 * @param position pozicija �vor prije onog kojeg �elimo pobrisat
 * @return EXIT_SUCCESS
 */
int stateList_deleteNodeAfter(StateListP position);

/**
 * Pobri�i cijelu listu i sve gradove u njima
 *
 * @param head glava vezane liste
 * @return EXIT_SUCCESS
 */
int stateList_deleteAll(StateListP head);

/**
 * Ispi�i iz liste sve dr�ave i njegove gradove
 *
 * @param head glava vezane liste
 * @return EXIT_SUCCESS
 */
int stateList_print(StateListP head);

/**
 * Prona�i dr�avu iz liste po imenu
 *
 * @param head glava vezane liste
 * @param name ime dr�ave koju tra�imo
 * @return adresu �vora ako je prona�en, u suprotnom NULL
 */
StateListP stateList_findByName(StateListP head, char* name);