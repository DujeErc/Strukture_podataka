
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128
#define MAX_LINE_LEN 1024

struct _node;
typedef struct _node Node;
bool loadFromFile(char* buffer);
bool processExpression(char* expression, int* result, Node* head);
bool calculate(char operator, Node* head);
bool push(int num, Node* head);
bool pop(int* num, Node* head);
void deleteAll(Node* n);

typedef struct _node
{
	int num;
	Node* next;
} Node;

int main(void)
{
	char expression[MAX_LINE_LEN] = { 0 };
	int result = 0;
	bool prExp_ret = false;
	Node* head = NULL;
	head = (Node*)malloc(sizeof(Node));

	if (!head)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}

	head->next = NULL;

	printf("Postfix Expression Calculator\n\n");
	while (!loadFromFile(expression));
	prExp_ret = processExpression(expression, &result, head);
	deleteAll(head);

	if (prExp_ret)
	{
		// printa konacni rezultat
		printf("Result = %d", result);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

bool loadFromFile(char* buffer)
{
	char filename[MAX_STR_LEN] = { 0 };
	FILE* f = NULL;

	printf("Please type in the file name: ");
	scanf_s(" %s", &filename, MAX_STR_LEN);
	f = fopen(filename, "r");
	if (!f)
	{
		printf("ERROR: File %s could not be opened! Please try again\n", filename);
		return false;
	}

	fgets(buffer, MAX_LINE_LEN, f);

	return true;
}

//procesira matematicki izraz
bool processExpression(char* expression, int* result, Node* head)
{
	int num = 0;
	char operator = 0;
	int temp = 0;
	int numOfBytes = 0;

	while (strlen(expression) > 0)
	{
		temp = sscanf(expression, " %d %n", &num, &numOfBytes);
		if (temp == 1)
		{
			if (!push(num, head))
			{
				printf("ERROR: Out of memory\n");
				return false;
			}
		}
		else {
			sscanf(expression, " %c %n", &operator, &numOfBytes);
			if (!calculate(operator, head)) return false;
		}
		expression += numOfBytes;
	}

	// popa konacni rezultat
	pop(result, head);

	// provjerava jel stack prazan
	if (head->next)
	{
		printf("ERROR: Invalid mathematical expression\n");
		return false;
	}

	return true;
}


bool calculate(char operator, Node* head)
{
	int firstOperand = 0;
	int secondOperand = 0;
	int result = 0;

	if (!pop(&secondOperand, head) || !pop(&firstOperand, head))
	{
		printf("ERROR: Invalid mathematical expression\n");
		return false;
	}

	switch (operator)
	{
	case '+':
		result = firstOperand + secondOperand;
		break;
	case '-':
		result = firstOperand - secondOperand;
		break;
	case '*':
		result = firstOperand * secondOperand;
		break;
	case '/':
		if (secondOperand == 0)
		{
			printf("ERROR: Division by zero\n");
			return false;
		}
		result = firstOperand / secondOperand;
		break;
	default:
		printf("ERROR:Invalid operator\n");
		return false;
	}

	// pusha rezultat u stack
	if (push(result, head))
	{
		return true;
	}
	else
	{
		printf("ERROR: Out of memory\n");
		return false;
	}
}

bool push(int num, Node* head)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return false;

	new->next = head->next;
	head->next = new;
	new->num = num;

	return true;
}
//popa broj iz stacka
bool pop(int* num, Node* head)
{
	Node* popped = head->next;

	if (popped)
	{
		*num = popped->num;
		//deleta popani node
		head->next = head->next->next;
		free(popped);

		return true;
	}
	return false;
}


void deleteAll(Node* n)
{
	Node* temp = NULL;

	while ((temp = n) != NULL)
	{
		n = n->next;
		free(temp);
	}
}