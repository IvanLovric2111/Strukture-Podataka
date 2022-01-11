#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

struct _grad;
typedef struct _grad* Pozicija;
typedef struct _grad {
    char imeGrada[MAX_SIZE];
    int broj;
    Pozicija next;
}grad;

struct _drzava;
typedef struct _drzava* Stablo;
typedef struct _drzava {
    char imeDrzave[MAX_SIZE];
    Stablo L;
    Stablo D;
    grad head;
}drzava;

int File1(Stablo root, char* fileName);
int InsertSorted(Pozicija head, char* imeGrada, int broj);
int CreateElement(Pozicija element, char* imeGrada, int broj);
int InsertAfter(Pozicija el, Pozicija newElement);
int File2(Stablo el, char* fileName);
Stablo Tree(Stablo root, char* imeDrzave, char* fileName);
Stablo MakeTree(char* imeDrzave);
int PrintCountries(Stablo root);
int PrintCities(Pozicija head);
int SearchCountries(Stablo root);
Stablo SearchTree(Stablo root, char* ime);
int SearchCities(Pozicija head, int broj, int* i);
int FreeAll(Stablo root);
int FreeList(Pozicija head);

int main()
{
    Stablo root = NULL;

    root = File1(root, "drzave.txt");

    PrintCountries(root);

    SearchCountries(root);

    FreeAll(root);

    return EXIT_SUCCESS;
}

int File1(Stablo root, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_LINE] = { 0 };
    char imeDrzave[MAX_SIZE] = { 0 };
    char datotekaGrad[MAX_SIZE] = { 0 };

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp);

        sscanf(buffer, " %s %s", imeDrzave, datotekaGrad);
        root = Tree(root, imeDrzave, datotekaGrad);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int InsertSorted(Pozicija head, char* imeGrada, int broj)
{
    Pozicija temp1 = head;
    Pozicija temp2 = head->next;
    Pozicija newElement = NULL;

    while (temp2)
    {
        if (temp2->broj > broj)
        {
            CreateElement(temp1, imeGrada, broj);
            return EXIT_SUCCESS;
        }

        else if (temp2->broj == broj)
            if (strcmp(temp2->imeGrada, imeGrada) > 0)
            {
                CreateElement(temp1, imeGrada, broj);
                return EXIT_SUCCESS;
            }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    CreateElement(temp1, imeGrada, broj);


    return EXIT_SUCCESS;
}

int CreateElement(Pozicija element, char* imeGrada, int broj)
{
    Pozicija newElement = NULL;

    newElement = (Pozicija)malloc(sizeof(grad));
    if (!newElement)
    {
        perror("Greska alociranja!\n");
        return EXIT_FAILURE;
    }

    strcpy(newElement->imeGrada, imeGrada);
    newElement->broj = broj;
    newElement->next = NULL;

    InsertAfter(element, newElement);

    return EXIT_SUCCESS;
}

int InsertAfter(Pozicija el, Pozicija newElement)

{
    newElement->next = el->next;
    el->next = newElement;

    return EXIT_SUCCESS;
}

int File2(Stablo el, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_LINE] = { 0 };
    char imeGrada[MAX_SIZE] = { 0 };
    int broj = 0;

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return EXIT_FAILURE;
    }

    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp);

        sscanf(buffer, " %s %d", imeGrada, &broj);
        InsertSorted(&el->head, imeGrada, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

Stablo Tree(Stablo root, char* imeDrzave, char* fileName)
{
    if (!root)
    {
        root = MakeTree(imeDrzave);
        File2(root, fileName);
    }

    else if (strcmp(root->imeDrzave, imeDrzave) > 0)
        root->L = Tree(root->L, imeDrzave, fileName);

    else
        root->D = Tree(root->D, imeDrzave, fileName);

    return root;
}

Stablo MakeTree(char* imeDrzave)
{
    Stablo newElement = NULL;
    newElement = (Stablo)malloc(sizeof(drzava));
    if (!newElement)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(newElement->imeDrzave, imeDrzave);
    strcpy(newElement->head.imeGrada, "");
    newElement->head.broj = 0;
    newElement->L = NULL;
    newElement->D = NULL;

    return newElement;
}

int PrintCountries(Stablo root)
{
    if (root->L)
        PrintCountries(root->L);

    printf("%s\n", root->imeDrzave);
    PrintCities(&root->head);

    if (root->D)
        PrintCountries(root->D);

    return EXIT_SUCCESS;
}

int PrintCities(Pozicija head)
{
    while (head->next)
    {
        printf("    %s\n", head->next->imeGrada);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int SearchCountries(Stablo root)
{
    char ime[MAX_SIZE] = { 0 };
    int broj = 0, i = 0;
    Stablo temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    temp = SearchTree(root, ime);
    if (!temp)
    {
        printf("Drzava ne postoji!\n");
        return EXIT_FAILURE;
    }

    printf("Upisite broj stanovnika za usporedbu:\n");
    scanf(" %d", &broj);
    SearchCities(&temp->head, broj, &i);

    return EXIT_SUCCESS;
}

Stablo SearchTree(Stablo root, char* ime)
{
    if (!strcmp(root->imeDrzave, ime))
        return root;

    else if (strcmp(root->imeDrzave, ime) > 0)
        SearchTree(root->D, ime);

    else
        SearchTree(root->L, ime);

    return NULL;
}

int SearchCities(Pozicija head, int broj, int* i)
{
    while (head->next)
    {
        if (head->next->broj > broj)
        {
            (*i)++;
            printf("%s\n", head->next->imeGrada);
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int FreeAll(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeList(&root->head);

    FreeAll(root->L);

    FreeAll(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int FreeList(Pozicija head)
{
    Pozicija temp = NULL;

    while (head->next)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}