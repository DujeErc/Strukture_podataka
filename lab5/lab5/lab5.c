#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to push a node onto the stack
void push(struct Node** top, int data) {
    struct Node* node = newNode(data);
    node->next = *top;
    *top = node;
}

// Function to pop and return a node from the stack
int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        exit(1);
    }
    struct Node* temp = *top;
    *top = (*top)->next;
    int data = temp->data;
    free(temp);
    return data;
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* expression) {
    struct Node* stack = NULL;
    int i = 0;

    while (expression[i]) {
        if (isdigit(expression[i])) {
            int num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            push(&stack, num);
        }
        else if (expression[i] == ' ') {
            i++;
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (expression[i]) {
            case '+':
                push(&stack, operand1 + operand2);
                break;
            case '-':
                push(&stack, operand1 - operand2);
                break;
            case '*':
                push(&stack, operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0) {
                    printf("Error: Division by zero.\n");
                    exit(1);
                }
                push(&stack, operand1 / operand2);
                break;
            default:
                printf("Error: Invalid operator: %c\n", expression[i]);
                exit(1);
            }
            i++;
        }
        else if (expression[i] == '\n') {
            i++;
        }
        else {
            printf("Error: Invalid character: %c\n", expression[i]);
            exit(1);
        }
    }
    if (stack == NULL) {
        printf("Error: Empty expression.\n");
        exit(1);
    }
    int result = pop(&stack);
    if (stack != NULL) {
        printf("Error: Invalid expression.\n");
        exit(1);
    }
    return result;
}

int main() {
    char expression[100];
    printf("Enter the postfix expression: ");
    fgets(expression, sizeof(expression), stdin);
    int result = evaluatePostfix(expression);
    printf("Result of the postfix expression: %d\n", result);
    return 0;
}
