#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)

struct _Polinom;
typedef struct _Polinom* Position;
typedef struct _Polinom
{
	int koeficijent;
	int eksponent;
	Position next;
} Polinom;

int Procitaj(Position head1, Position head2, char* imedatoteke);
int SortiraniUnos(Position head, Position newElement);
int Merge(Position position, Position newElement);
Position KreirajElement(int koeficijent, int eksponent);
int Ispis(Position head);
int Unesi(int koeficijent, int eksponent, Position position);
int UnesiIza(Position position, Position newElement);
int Zbroji(Position resultHead, Position head1, Position head2);
int Pomnozi(Position resultHead, Position head1, Position head2);

int main()
{
	Polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom suma = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom umnozak = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	char imedatoteke[MAX_SIZE] = { 0 };

	if (Procitaj(&head1, &head2, imedatoteke) == EXIT_SUCCESS)
	{
		Zbroji(&suma, &head1, &head2);
		Pomnozi(&umnozak, &head1, &head2);

		Ispis(&suma);
		Ispis(&umnozak);
	}

	return EXIT_SUCCESS;
}

int Procitaj(Position head1, Position head2, char* imedatoteke)
{
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };
	char* currentBuffer = NULL;
	int koeficijent = 0;
	int eksponent = 0;
	int pomak = 0;
	Position newElement = NULL;

	printf("Unesi ime datoteke:\n");
	scanf(" %s", imedatoteke);

	datoteka = fopen(imedatoteke, "r");
	if (!datoteka)
	{
		perror("Greska s otvaranjem datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, datoteka);
	currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		sscanf(currentBuffer, " %d %d %n", &koeficijent, &eksponent, &pomak);

		newElement = KreirajElement(koeficijent, eksponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		SortiraniUnos(head1, newElement);

		currentBuffer += pomak;
	}

	fgets(buffer, MAX_LINE, datoteka);
	currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		sscanf(currentBuffer, " %d %d %n", &koeficijent, &eksponent, &pomak);
		
		newElement = KreirajElement(koeficijent, eksponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		SortiraniUnos(head2, newElement);

		currentBuffer += pomak;
	}

	fclose(datoteka);

	return EXIT_SUCCESS;
}

int Merge(Position position, Position newElement)
{
	if (position->next == NULL || position->next->eksponent != newElement->eksponent)
	{
		newElement->next = position->next;
		position->next = newElement;
	}
	else
	{
		int noviKoeficijent = position->next->koeficijent + newElement->koeficijent;
		if (noviKoeficijent == 0)
		{
			Position izbrisi = NULL;

			izbrisi = position->next;
			position->next = izbrisi->next;
			free(izbrisi);
		}
		else
		{
			position->next->koeficijent = noviKoeficijent;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}

int SortiraniUnos(Position head, Position newElement)
{
	Position temp = head;

	while (temp->next != NULL && temp->next->eksponent < newElement->eksponent)
	{
		temp = temp->next;
	}

	Merge(temp, newElement);

	return EXIT_SUCCESS;
}

Position KreirajElement(int koeficijent, int eksponent)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Polinom));
	if (!element)
	{
		perror("Greska s alokacijom!");
		return element; 
	}

	element->koeficijent = koeficijent;
	element->eksponent = eksponent;
	element->next = NULL;

	return element;
}

int Unesi(int koeficijent, int eksponent, Position position)
{
	Position newElement = KreirajElement(koeficijent, eksponent);
	if (!newElement)
	{
		return EXIT_FAILURE;
	}

	UnesiIza(position, newElement);
	position = position->next;

	return EXIT_SUCCESS;

}

int Zbroji(Position head, Position head1, Position head2)
{
	Position i = head1->next;
	Position j = head2->next;
	Position k = head;
	Position temp = NULL;

	while (i != NULL && j != NULL)
	{
		if (i->eksponent == j->eksponent)
		{
			Unesi(i->koeficijent + j->koeficijent, i->eksponent, k);
			i = i->next;
			j = j->next;
		}
		else if (i->eksponent < j->eksponent)
		{
			Unesi(i->koeficijent, i->eksponent, k);
			i = i->next;
		}
		else
		{
			Unesi(j->koeficijent, j->eksponent, k);
			j = j->next;
		}

	}
	if (i == NULL)
	{
		temp = j;
	}
	else
	{
		temp = i;
	}
	while (temp != NULL)
	{
		Unesi(temp->koeficijent, temp->eksponent, k);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int Pomnozi(Position head, Position head1, Position head2)
{
	Position i = head1->next;
	Position j = head2->next;
	
	while(i != NULL)
	{
		j = head2->next;
		while (j != NULL)
		{
			Position newElement = KreirajElement(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);
			if (!newElement)
			{
				return EXIT_FAILURE;
			}

			SortiraniUnos(head, newElement);
			j = j->next;
		}
		i = i->next;
	}

	return EXIT_SUCCESS;
}

int Ispis(Position head)
{
	Position temp = head->next;

	while (temp != NULL) {
		printf("%dx^%d", head->koeficijent, head->eksponent);
		if (head->next != NULL && head->next->koeficijent > 0)
			printf("+");
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int UnesiIza(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}
