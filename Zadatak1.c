#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE (1024)
#define MAXSIZE (128)

typedef struct student {
	char ime[MAXSIZE];
	char prezime[MAXSIZE];
	double bodovi;
};

int brojredaka(char* imedatoteke);
student* bodovistudenata(int brojstudenata, char* imedatoteke);
void ispis(student* studenti, int brojstudenata);


int main()
{
	int n = 0;
	student* students = NULL;
	char* nazivdatoteke = "studenti.txt";

	n = brojredaka(nazivdatoteke);

	if (n == -1)
	{
		return 0;
	}

	students = bodovistudenata(n, nazivdatoteke);

	if (students == NULL)
	{
		return 0;
	}

	ispis(students, n);

	return 0;
}

int brojredaka(char* imedatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAXLINE] = { 0 };

	datoteka = fopen(imedatoteke, "r");

	if (!datoteka)
	{
		printf("Gre?ka!");
		return -1;
	}
	while (!feof(datoteka))
	{
		fgets(buffer, MAXLINE, datoteka);
		brojac++;
	}

	fclose(datoteka);

	return brojac;
}

student* bodovistudenata(int brojstudenata, char* imedatoteke)
{
	student* studenti = NULL;
	FILE* datoteka = NULL;
	int brojac = 0;

	studenti = (student*)malloc(brojstudenata * sizeof(student));
	datoteka = fopen(imedatoteke, "r");

	if (!studenti)
	{
		printf("Gre?ka alociranja!");
		free(studenti);
		return NULL;
	}
	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

void ispis(student* studenti, int brojstudenata)
{
	double relativnibodovi[] = { 0 };
	int i = 0;
	int max = 0;

	max = studenti[0].bodovi;

	for (i = 1; i < brojstudenata; i++)
	{
		if (max < studenti[i].bodovi) max = studenti[i].bodovi;
	}

	for (i = 0; i < brojstudenata; i++)
	{
		relativnibodovi[i] = studenti[i].bodovi / max * 100;
	}

	for (i = 0; i < brojstudenata; i++)
	{
		printf("%s %s %lf %lf", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativnibodovi[i]);
	}
}