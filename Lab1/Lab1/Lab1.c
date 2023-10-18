
/*. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_ERROR_OPEN -1
#define EXIT_SUCCESS 0
#define MAX_LINE 1024
#define MAX_SIZE 50
#define max_br_bodova 120

typedef struct _student{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double score;
} Student; 

int ReadNORowsInFile() {
	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("students.txt", "r");

	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}


	fclose(filePointer);

	return counter;
}

int EnterStudents(int number, Student* s)
{
	int i = 0;
	FILE* f = NULL;
	f = fopen("students.txt", "r");
	if (f == NULL)
	{
		printf("Failed in file opening!");
		return FILE_ERROR_OPEN;
	}

	for (i = 0; i < number; i++)
		fscanf(f, "%s %s %lf", (s + i)->name, (s + i)->surname, &(s + i)->score);

	fclose(f);
	return EXIT_SUCCESS;
}


int FindMax(int number, Student* s)
{
	int i = 0, max = 0;
	for (i = 0; i < number; i++)
	{
		if ((s + i + 1)->score > (s + i)->score)
			max = (s + i + 1)->score;
	}

	return max;
}

int PrintStudents(int number, Student* s)
{
	int i;
	for (i = 0; i < number; i++)
		printf("Student: %s %s\nAbsolutely score %.2lf\nRelative score: %lf\n", (s + i)->name, (s + i)->surname, (s + i)->score, (double)((s + i)->score / max_br_bodova) * 100);
	return EXIT_SUCCESS;
}


int main()
{

	int m = 0, n = 0, max = 0;
	Student* st = NULL;
	int result = 0;
	result = ReadNORowsInFile();
	printf("Number of students in file is %d\n", result);

	st = (Student*)malloc(result * sizeof(Student));
	if (st == NULL)
	{
		printf("Failed in dynamic allocation!");
		return -1;
	}
	m = EnterStudents(result, st);

	if (m != EXIT_SUCCESS)
		return FILE_ERROR_OPEN;


	max = FindMax(result, st);
	n = PrintStudents(result, st, max);
	free(st);

	return EXIT_SUCCESS;
}