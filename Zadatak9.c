#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUMBER (90)
#define MIN_NUMBER (10)
#define MAX_SIZE (100)

typedef struct stablo* Stablo;
typedef struct stablo {
    int broj;
    Stablo desno;
    Stablo lijevo;
};

typedef struct cvor* Pozicija;
typedef struct cvor {
    int broj;
    Pozicija next;
};

Stablo Insert(Stablo root, int broj);
Stablo CreateElement(int broj);
int InorderPrint(Stablo root);
int FreeAll(Stablo root);
int Replace(Stablo root);
int MakeList(Stablo root, Pozicija head);
int InsertList(Pozicija head, int broj);
Pozicija CreateList(int broj);
int Datoteka(Pozicija head);
int DeleteAll(Pozicija head);
int DeleteAfter(Pozicija position);


int main()
{
    Stablo root = NULL;
    Pozicija head = NULL;
    int i = 0;
    int niz[11] = {2,5,7,8,11,1,4,2,3,7};

    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++)
        root = Insert(root, niz[i]);
       
    InorderPrint(root);
    printf("\n");
    MakeList(root, &head);
    Datoteka(&head);

    Replace(root);
    InorderPrint(root);
    printf("\n");
    MakeList(root, &head);
    Datoteka(&head);

    FreeAll(root);

    root = NULL;
    for (i = 0; i < 10; i++)
        root = Insert(root, rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER);

    InorderPrint(root);
    printf("\n");
    MakeList(root, &head);
    Datoteka(&head);

    Replace(root);
    InorderPrint(root);
    printf("\n");
    MakeList(root, &head);
    Datoteka(&head);

    FreeAll(root);

    return EXIT_SUCCESS;
}

Stablo Insert(Stablo root, int broj)
{
    if (!root)
        root = CreateElement(broj);

    else if (broj >= root->broj)
        root->lijevo = Insert(root->lijevo, broj);

    else
        root->desno = Insert(root->desno, broj);

    return root;
}

Stablo CreateElement(int broj)
{
    Stablo novi = NULL;
    novi = (Stablo)malloc(sizeof(struct stablo));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    novi->broj = broj;
    novi->lijevo = NULL;
    novi->desno = NULL;

    return novi;
}

int InorderPrint(Stablo root)
{
    if (root->desno)
        InorderPrint(root->desno);

    printf("%d ", root->broj);

    if (root->lijevo)
        InorderPrint(root->lijevo);

    return EXIT_SUCCESS;
}

int FreeAll(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeAll(root->lijevo);

    FreeAll(root->desno);

    free(root);

    return EXIT_SUCCESS;
}

int Replace(Stablo root)
{
    int desno = 0, lijevo = 0;

    if (root->desno)
        desno = root->desno->broj + Replace(root->desno);

    if (root->lijevo)
        lijevo = root->lijevo->broj + Replace(root->lijevo);

    root->broj = desno + lijevo;

    return root->broj;
}

int MakeList(Stablo root, Pozicija head)
{
    if (root->desno)
        MakeList(root->desno, head);

    InsertList(head, root->broj);

    if (root->lijevo)
        MakeList(root->lijevo, head);

    return EXIT_SUCCESS;
}

int InsertList(Pozicija head, int broj)
{
    Pozicija novi = NULL;

    novi = CreateList(broj);

    while (head->next)
        head = head->next;

    head->next = novi;

    return EXIT_SUCCESS;
}

Pozicija CreateList(int broj)
{
    Pozicija novi = NULL;
    novi = (Pozicija)malloc(sizeof(struct cvor));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    novi->broj = broj;
    novi->next = NULL;

    return novi;
}

int Datoteka(Pozicija head)
{
    FILE* fp = NULL;
    char ime[MAX_SIZE] = { 0 };

    printf("Kako ce se zvati datoteka?\n");
    scanf(" %s", ime);

    fp = fopen(ime, "a");
    if (!fp)
    {
        printf("Nemoguce otvoriti datoteku!\n");
        return EXIT_FAILURE;
    }

    while (head->next)
    {
        fprintf(fp, "%d ", head->next->broj);
        head = head->next;
    }

    fprintf(fp, "\n");

    DeleteAll(head);

    fclose(fp);

    return EXIT_SUCCESS;
}

int DeleteAll(Pozicija head)
{
    while (head->next)
    {
        DeleteAfter(head);
    }

    return EXIT_SUCCESS;
}

int DeleteAfter(Pozicija position)
{
    Pozicija temp = position->next;

    position->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}
