#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

struct _grad;
typedef struct _grad* Stablo;
typedef struct _grad {
    char imeGrada[MAX_SIZE];
    int broj;
    Stablo L;
    Stablo D;
}grad;

struct _drzava;
typedef struct _drzava* Pozicija;
typedef struct _drzava {
    char imeDrzave[MAX_SIZE];
    Stablo root;
    Pozicija next;
}drzava;

int File1(Pozicija head, char* fileName);
int InsertSorted(Pozicija head, char* imeDrzave, char* fileName);
Pozicija CreateElement(Pozicija element, char* imeDrzave);
int InsertAfter(Pozicija el, Pozicija newElement);
int File2(Pozicija el, char* fileName);
Stablo Tree(Stablo root, char* imeG, int broj);
Stablo MakeTree(char* imeGrada, int broj);
int PrintCountries(Pozicija head);
int PrintCities(Stablo root);
int SearchCountries(Pozicija head);
int SearchCities(Stablo root, int broj, int* i);
int FreeAll(Pozicija head);
int FreeTree(Stablo root);

int main()
{
    drzava head = { .imeDrzave = {0}, .root = NULL, .next = NULL };

    File1(&head, "drzave.txt");

    PrintCountries(&head);

    SearchCountries(&head);

    FreeAll(&head);

    return EXIT_SUCCESS;
}

int File1(Pozicija head, char* fileName)
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
        InsertSorted(head, imeDrzave, datotekaGrad);

    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int InsertSorted(Pozicija head, char* imeDrzave, char* fileName)
{
    Pozicija temp1 = head;
    Pozicija temp2 = head->next;
    Pozicija newElement = NULL;

    while (temp2)
    {
        if (strcmp(temp2->imeDrzave, imeDrzave) > 0)
        {
            newElement = CreateElement(temp1, imeDrzave);
            File2(newElement, fileName);
            return EXIT_SUCCESS;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return EXIT_SUCCESS;
}

Pozicija CreateElement(Pozicija element, char* imeDrzave)
{
    Pozicija newElement = NULL;

    newElement = (Pozicija)malloc(sizeof(drzava));
    if (!newElement)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(newElement->imeDrzave, imeDrzave);
    newElement->root = NULL;
    newElement->next = NULL;

    InsertAfter(element, newElement);

    return newElement;
}

int InsertAfter(Pozicija el, Pozicija newElement)
{
    newElement->next = el->next;
    el->next = newElement;

    return EXIT_SUCCESS;
}

int File2(Pozicija el, char* fileName)
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
        el->root = Tree(el->root, imeGrada, broj);
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
        if (strcmp(root->imeGrada, imeG) < 0)
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

Stablo MakeTree(char* imeGrada, int broj)
{
    Stablo newElement = NULL;
    newElement = (Stablo)malloc(sizeof(grad));
    if (!newElement)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(newElement->imeGrada, imeGrada);
    newElement->broj = broj;
    newElement->L = NULL;
    newElement->D = NULL;

    return newElement;
}

int PrintCountries(Pozicija head)
{
    while (head->next)
    {
        printf("%s\n", head->next->imeDrzave);
        PrintCities(head->next->root);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int PrintCities(Stablo root)
{
    if (root->L)
        PrintCities(root->L);

    printf("  %s\n", root->imeGrada);

    if (root->D)
        PrintCities(root->D);

    return EXIT_SUCCESS;
}

int SearchCountries(Pozicija head)
{
    char ime[MAX_SIZE] = { 0 };
    int broj = 0, i = 0;
    Pozicija temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    while (head->next)
    {
        if (!strcmp(head->next->imeDrzave, ime))
        {
            temp = head->next;
            break;
        }
        head = head->next;
    }

    if (!head->next)
    {
        printf("Drzava ne postoji!\n");
        return EXIT_FAILURE;
    }

    printf("Upisite broj stanovnika za usporedbu:\n");
    scanf(" %d", &broj);
    SearchCities(temp->root, broj, &i);

    if (!i)
        printf("Nepostojeci gradovi!\n");

    return EXIT_SUCCESS;
}

int SearchCities(Stablo root, int broj, int* i)
{
    if (root->broj > broj)
    {
        printf("%s\n", root->imeGrada);
        (*i)++;
        if (root->L)
            if (root->L->broj > broj)
                SearchCities(root->L, broj, i);
    }

    if (root->D)
        if (root->D->broj > broj)
            SearchCities(root->D, broj, i);

    return EXIT_SUCCESS;
}

int FreeAll(Pozicija head)
{
    Pozicija temp = head->next;
    
    while (head->next)
    {
        FreeTree(head->next->root);
        head->next = temp->next;
        free(temp);
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
