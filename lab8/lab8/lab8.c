#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cvor* pozicija;
typedef struct cvor {
    int br;
    pozicija left;
    pozicija right;
} cvor;

static int brojac = 0;

cvor* stvaranje();
pozicija insert(pozicija, pozicija);
pozicija find(pozicija, int);
pozicija deleteNode(pozicija, int);
pozicija findMax(pozicija);
pozicija findMin(pozicija);
pozicija printInorder(pozicija);
pozicija printPreorder(pozicija);
pozicija printPostorder(pozicija);
int clear(pozicija*);
int userInterface(pozicija, pozicija);

int main()
{
    pozicija root = NULL;
    root = stvaranje();
    userInterface(root, root);
    return 0;
}

int userInterface(pozicija p, pozicija root)
{
    int check = 1;
    int n;
    while (check == 1)
    {
        printf("\nOdaberite\n");
        printf("A-Unos\n");
        printf("B-Brisanje\n");
        printf("C-Pronalazenje elementa\n");
        printf("D-Ispis elemenata - inorder\n");
        printf("E-Ispis elemenata - preorder\n");
        printf("F-Ispis elemenata - postorder\n");
        printf("X-Izlaz iz programa\n");

        char c = { 0 };
        scanf(" %c", &c);
        c = toupper(c);
        switch (c)
        {
        case 'A':
            printf("Unesite broj koji zelite unijeti\n");
            if (scanf("%d", &n) == 1)
            {
                if (brojac == 0) {
                    p->br = n;
                    brojac++;
                }
                else {
                    pozicija q = NULL;
                    q = stvaranje();
                    q->br = n;
                    insert(p, q);
                    brojac++;
                }
            }
            else printf("Unesite broj\n");
            break;
        case 'B':
            printf("Unesite broj koji zelite izbrisati\n");
            if (scanf("%d", &n) == 1) {
                root = deleteNode(root, n);
            }
            else printf("Unesite broj\n");
            break;
        case 'C':
            printf("Unesite broj koji zelite naci\n");
            if (scanf("%d", &n) == 1)
            {
                if (!p->br)
                    printf("Taj broj ne postoji\n");
                else {
                    find(p, n);
                    if (p == NULL)
                        printf("Taj broj ne postoji\n");
                    else printf("Taj broj postoji\n");
                }
            }
            else
                printf("Unesite broj\n");
            p = root;
            break;
        case 'D':
            printInorder(p);
            break;
        case 'E':
            printPreorder(p);
            break;
        case 'F':
            printPostorder(p);
            break;
        case 'X':
            check = 0;
            clear(&root);
            break;
        default:
            printf("Unesite jedno od ponudenih slova\n");
            break;
        }
    }
    return 0;
}

cvor* stvaranje()
{
    cvor* c = NULL;
    c = malloc(sizeof(cvor));
    if (NULL == c) {
        printf("Greska u alokaciji memorije\n");
    }
    else
    {
        c->left = NULL;
        c->right = NULL;
    }
    return c;
}

pozicija insert(pozicija p, pozicija q)
{
    if (p == NULL)
        return q;
    if (p->br < q->br)
        p->right = insert(p->right, q);
    else if (p->br > q->br)
        p->left = insert(p->left, q);
    else
        free(q);
    return p;
}

pozicija find(pozicija p, int n)
{
    if (p == NULL)
        return NULL;
    else if (p->br > n)
        return find(p->left, n);
    else if (p->br < n)
        return find(p->right, n);
    else return p;
}

pozicija deleteNode(pozicija p, int n)
{
    if (p == NULL)
        return NULL;
    if (p->br > n)
        p->left = deleteNode(p->left, n);
    else if (p->br < n)
        p->right = deleteNode(p->right, n);
    else {
        if (p->left) {
            pozicija temp = findMax(p->left);
            p->br = temp->br;
            p->left = deleteNode(p->left, temp->br);
        }
        else if (p->right) {
            pozicija temp = findMin(p->right);
            p->br = temp->br;
            p->right = deleteNode(p->right, temp->br);
        }
        else {
            free(p);
            return NULL;
        }
    }
    brojac--;
    return p;
}

pozicija findMax(pozicija p)
{
    while (p->right != NULL)
        p = p->right;
    return p;
}

pozicija findMin(pozicija p)
{
    while (p->left != NULL)
        p = p->left;
    return p;
}

pozicija printInorder(pozicija p)
{
    if (p == NULL) {
        return NULL;
    }
    p->left = printInorder(p->left);
    printf("%d ", p->br);
    p->right = printInorder(p->right);

    return p;
}

pozicija printPostorder(pozicija p)
{
    if (p == NULL)
        return NULL;
    p->left = printPostorder(p->left);
    p->right = printPostorder(p->right);
    printf("%d ", p->br);
    return p;
}

pozicija printPreorder(pozicija p)
{
    if (p == NULL)
        return NULL;
    printf("%d ", p->br);
    p->left = printPreorder(p->left);
    p->right = printPreorder(p->right);
    return p;
}

int clear(pozicija* p)
{
    if (*p != NULL)
    {
        clear(&((*p)->left));
        clear(&((*p)->right));
        free(*p);
        *p = NULL;
    }
    return 0;
}