#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
};

int UnosP(Position head, char* name, char* surname, int birthYear);
int Ispis(Position first);
int UnosK(Position head, char* name, char* surname, int birthYear);
Position TraziK(Position head);
int Trazi(char* surname, Position head);
Position TraziPrethodnog(Position clan, Position head);
int Brisi(Position clan, Position head);
int UnosIspred(Position clan, Position head, char* name, char* surname, int birthYear);
int UnosIza(Position clan, Position head, char* name, char* surname, int birthYear);
int Sortiraj(Position head);
int IzbrojiListu(Position head);
Position swap(Position p1, Position p2);
int Upisi(Position head);
int Procitaj(Position head);

int main(int argc, char** argv)
{
	_Person head;
	head.next = NULL;
	head.name = { 0 };
	head.surname = { 0 };
	head.birthYear = 0;
	Position p = &head;

	return EXIT_SUCCESS;
}

int UnosP(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;


	newPerson = (Position)malloc(sizeof(_Person));

	if (!newPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int Ispis(Position first)
{
	Position temp = first->next;
	while (temp)
	{
		printf("Name: %s, Surname: %s, "
			"birthYear: %d\n", temp->name, temp->surname,
			temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position TraziK(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;
}

int UnosK(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position lastPerson = NULL;


	newPerson = (Position)malloc(sizeof(_Person));

	if (!newPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	lastPerson = (Position)malloc(sizeof(_Person));

	if (!lastPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	lastPerson = TraziK(head);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	newPerson->next = lastPerson->next;
	lastPerson->next = newPerson;

	return EXIT_SUCCESS;
}

int Trazi(char* surname, Position head)
{
	Position temp = head->next;

	while (temp->surname != NULL && strcmp(temp->surname, surname) != 0)
		temp = temp->next;

	printf("Pronaden element liste.");

	return EXIT_SUCCESS;
}

Position TraziPrethodnog(Position clan, Position head)
{
	Position temp = head;

	while (temp != NULL && temp->next != clan)
	{
		temp = temp->next;
	}

	return temp;
}

int Brisi(Position clan, Position head)
{
	Position temp = NULL;
	temp = TraziPrethodnog(clan, head);

	temp->next = temp->next->next;
	free(clan);

	return EXIT_SUCCESS;
}

int UnosIspred(Position clan, Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position previousPerson = NULL;


	newPerson = (Position)malloc(sizeof(_Person));

	if (!newPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	previousPerson = (Position)malloc(sizeof(_Person));

	if (!previousPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	previousPerson = TraziPrethodnog(clan, head);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	newPerson->next = previousPerson->next;
	previousPerson->next = newPerson;

	return EXIT_SUCCESS;
}

int UnosIza(Position clan, Position head, char* name, char* surname, int birthYear)
{
	Position temp = head;
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(_Person));

	if (!newPerson)
		perror("Nemoguæe alocirati memoriju!\n");

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	while (temp != NULL && temp != clan)
	{
		temp = temp->next;
	}

	newPerson->next = temp->next;
	temp->next = newPerson;

	return EXIT_SUCCESS;
}

int IzbrojiListu(Position head)
{
	Position temp = head;
	int br = 0;

	while (temp->next)
	{
		br++;
		temp = temp->next;
	}

	return br;
}

Position swap(Position p1, Position p2)
{
	Position temp = NULL;
	Position temp = p2->next;
	p2->next = p1->next;
	p1->next = temp;
	
	return p2;
}

int Sortiraj(Position head)
{
	int n = 0;
	int i = 0;
	int j = 0;
	Position* h = NULL;

	n = IzbrojiListu(head);

	for (i = 0; i < n - 1; i++)
	{
		h = &head;

		for (j = 0; j < n - i - 1; j++)
		{
			Position p1 = *h;
			Position p2 = p1->next;

			if (strcmp(p1->surname, p2->surname) > 0)
			{
				*h = swap(p1, p2);
			}

			h = &(*h)->next;
		}
	}

	return EXIT_SUCCESS;
}

int Upisi(Position head)
{
	Position temp = head->next;
	FILE* datoteka = NULL;

	datoteka = fopen("vezanalista.txt", "w");

	if (!datoteka)
	{
		printf("Greška!");
	}

	while (temp)
	{
		fprintf(datoteka, "\n%s %s %d", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

int Procitaj(Position head)
{
	FILE* datoteka = fopen("vezanalista.txt", "r");
	char buffer[MAX_LINE] = { 0 };
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;

	if (!datoteka)
	{
		printf("Datoteka ne postoji!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		sscanf(buffer, " %s %s %d", name, surname, &birthYear);
		UnosK(head, name, surname, birthYear);
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}