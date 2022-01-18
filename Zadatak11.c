#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define P (11)

struct _grad;
typedef struct _grad* Stablo;
typedef struct _grad {
    char imeG[MAX_SIZE];
    int broj;
    Stablo L;
    Stablo D;
}grad;

struct _drzava;
typedef struct _drzava* Pozicija;
typedef struct _drzava {
    char imeD[MAX_SIZE];
    Stablo root;
    Pozicija next;
}drzava;

int DatotekaDrzave(Pozicija tablica, char* fileName);
int HashTab(char* imeD);
int SortUnos(Pozicija head, char* imeD, char* fileName);
Pozicija MakeEl(Pozicija head, char* imeD);
int Insert(Pozicija el, Pozicija new);
int DatotekaGradovi(Pozicija el, char* fileName);
Stablo Tree(Stablo root, char* imeG, int broj);
Stablo MakeTree(char* imeG, int broj);
int IspisDrzava(Pozicija tablica);
int IspisGrad(Stablo root);
int PretragaDrzava(Pozicija tablica);
int PretragaGradova(Stablo root, int broj, int* i);
int FreeAll(Pozicija tablica);
int FreeTree(Stablo root);
int Pop(Pozicija head);

int main()
{
    drzava tablica[P];
    int i = 0;
    while (i != P)
    {
        strcpy(tablica[i].imeD, "");
        tablica[i].root = NULL;
        tablica[i].next = NULL;
        i++;
    }

    DatotekaDrzave(tablica, "drzave.txt");

    IspisDrzava(tablica);

    PretragaDrzava(tablica);

    FreeAll(tablica);

    return EXIT_SUCCESS;
}

int DatotekaDrzave(Pozicija tablica, char* fileName)
{
    FILE* fp = NULL;
    fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = { 0 };
    char imeD[MAX_SIZE] = { 0 };
    char datotekaGrad[MAX_SIZE] = { 0 };

    if (!fp)
    {
        printf("Datoteka drzave nije otvorena!\n");
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if (sscanf(buffer, " %s %s", imeD, datotekaGrad) == 2)
            SortUnos(&tablica[HashTab(imeD) % P], imeD, datotekaGrad);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int HashTab(char* imeD)
{
    int i = 0;
    int suma = 0;

    while (i != 5)
    {
        suma += (int)imeD[i];
        i++;
    }

    return suma;
}

int SortUnos(Pozicija head, char* imeD, char* fileName)
{
    Pozicija tempPrev = head;
    Pozicija tempNext = head->next;
    Pozicija el = NULL;

    while (tempNext)
    {
        if (strcmp(tempNext->imeD, imeD) > 0)
        {
            el = MakeEl(tempPrev, imeD);
            DatotekaGradovi(el, fileName);
            return EXIT_SUCCESS;
        }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    el = MakeEl(tempPrev, imeD);
    DatotekaGradovi(el, fileName);

    return EXIT_SUCCESS;
}

Pozicija MakeEl(Pozicija el, char* imeD)
{
    Pozicija novi = NULL;

    novi = (Pozicija)malloc(sizeof(drzava));
    if (!novi)
    {
        perror("Greska alokacije!\n");
        return NULL;
    }

    strcpy(novi->imeD, imeD);
    novi->root = NULL;
    novi->next = NULL;

    Insert(el, novi);

    return novi;
}

int Insert(Pozicija el, Pozicija novi)
{
    novi->next = el->next;
    el->next = novi;

    return EXIT_SUCCESS;
}

int DatotekaGradovi(Pozicija el, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = { 0 };
    char imeG[MAX_SIZE] = { 0 };
    int broj = 0;

    if (!fp)
    {
        printf("Datoteka grad nije otvorena!\n");
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if (sscanf(buffer, " %s %d", imeG, &broj) == 2)
            el->root = Tree(el->root, imeG, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

Stablo Tree(Stablo root, char* imeG, int broj)
{
    Stablo temp = NULL;

    if (!root)
        root = MakeTree(imeG, broj);

    else if (broj < root->broj)
        root->L = Tree(root->L, imeG, broj);

    else if (broj > root->broj)
        root->D = Tree(root->D, imeG, broj);

    else
    {
        if (strcmp(root->imeG, imeG) < 0)
        {
            if (root->D->broj == broj)
                root->D = Tree(root->D, imeG, broj);

            else
            {
                temp = root->D;
                root->D = MakeTree(imeG, broj);
                root->D->D = temp;
            }
        }

        else
        {
            if (root->L->broj == broj)
                root->L = Tree(root->L, imeG, broj);

            else
            {
                temp = root->L;
                root->L = MakeTree(imeG, broj);
                root->L->L = temp;
            }
        }
    }

    return root;
}

Stablo MakeTree(char* imeG, int broj)
{
    Stablo new = NULL;
    new = (Stablo)malloc(sizeof(grad));
    if (!new)
    {
        perror("Greska alokacije!\n");
        return NULL;
    }

    strcpy(new->imeG, imeG);
    new->broj = broj;
    new->L = NULL;
    new->D = NULL;

    return new;
}

int IspisDrzava(Pozicija tablica)
{
    int i = 0;
    Pozicija head = NULL;

    while (i != P)
    {
        head = &tablica[i];
        while (head->next)
        {
            printf("%s\n", head->next->imeD);
            IspisGrad(head->next->root);
            head = head->next;
        }
        i++;
    }

    return EXIT_SUCCESS;
}

int IspisGrad(Stablo root)
{
    if (root->L)
        IspisGrad(root->L);

    printf("    %s\n", root->imeG);

    if (root->D)
        IspisGrad(root->D);

    return EXIT_SUCCESS;
}

int PretragaDrzava(Pozicija tablica)
{
    char ime[MAX_SIZE] = { 0 };
    int broj = 0, i = 0, br = 0, check = 0;
    Pozicija temp = NULL, head = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    while (br != P)
    {
        head = &tablica[br];
        while (head->next)
        {
            if (!strcmp(head->next->imeD, ime))
            {
                temp = head->next;
                check++;
                break;
            }
            head = head->next;
        }
        if (check)
            break;
        br++;
    }

    if (!check)
    {
        printf("Nepostojeca drzava!\n");
        return -1;
    }

    printf("Upisite broj stanovnika da vidite koji gradovi imaju vise stanovnika od tog broja.\n");
    scanf(" %d", &broj);
    PretragaGradova(temp->root, broj, &i);

    if (!i)
        printf("Nepostojeci grad!\n");

    return EXIT_SUCCESS;
}

int PretragaGradova(Stablo root, int broj, int* i)
{
    if (root->broj > broj)
    {
        printf("%s\n", root->imeG);
        (*i)++;
        if (root->L)
            if (root->L->broj > broj)
                PretragaGradova(root->L, broj, i);
    }

    if (!root->D)
        return EXIT_SUCCESS;

    if (root->D->broj > broj)
        PretragaGradova(root->D, broj, i);

    return EXIT_SUCCESS;
}

int FreeAll(Pozicija tablica)
{
    int i = 0;
    Pozicija head = NULL;

    while (i != P)
    {
        head = &tablica[i];
        while (head->next)
        {
            FreeTree(head->next->root);
            Pop(head);
        }
        i++;
    }

    return EXIT_SUCCESS;
}

int FreeTree(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeTree(root->L);

    FreeTree(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int Pop(Pozicija head)
{
    Pozicija temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}