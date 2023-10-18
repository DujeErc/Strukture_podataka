/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _Person;
typedef struct _Person

Position findLast(Position head) {
	Position current = head;

	while (current->next != NULL) {
		current = current->next;
	}
	return current; //
}

int addToEndOfTheList(Position head) {
	
	Position newPerson = NULL;
	Position last = NULL;
		
	newPerson = createPerson();

	if (newPerson) {
		last = findLast(head);				//nemoj zaminit ove dvi linije koda bi stvoria loop
		newPerson->next = newPerson;		// u kojem element ima pokazivač na samog sebe
	}

	return EXIT_SUCCESS;

}
int printList(Position firstElement) {
	Position current = firstElement;
	if (!firstElement)
	{
		printf("Empty list!\n");
	}
	for (; current != NUll; current = current->next)
	{
		printPerson();
	}
}
int main()
{
	Person head = {}



}
Position createPerson

int menu(Position head) {
	
		Position person = NULL;
		while (1) {
			printf("Enter A(Add to the front of the list), )");
			scanf°(% c, c);
		}

	


}