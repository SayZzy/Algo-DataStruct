#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
    int head;
    struct cell* tail;
}* list;

void add_array(int a[], int *n, int i, int x) {
    for (int j = *n - 1; j >= i; j--) {
        a[j + 1] = a[j];
    }
    a[i] = x;
    (*n)++;
}

void remove_array(int a[], int *n, int i) {
    for (int j = i; j <= *n - 2; j++) {
        a[j] = a[j + 1];
    }
    (*n)--;
}

void stack_push(int S[], int N, int *n, int x) {
    if (*n >= N) {
        return;
    }
    S[*n] = x;
    (*n)++;
}

int stack_pop(int S[], int N, int *n) {
    if (*n <= 0) {
        return -1;
    }
    int x = S[*n - 1];
    (*n)--;
    return x;
}

int stack_peek(int S[], int n) {
    if (n <= 0) {
        return -1;
    }
    return S[n - 1];
}

void enqueue(list *Q, int x)
{
    list l = malloc(sizeof(struct cell));
    if (l == NULL) {
        return;
    }
    l->head = x;
    l->tail = NULL;
    if (*Q == NULL)
    {
        *Q = l;
        return;
    }
    list p = *Q;
    while (p->tail != NULL)
    {
        p = p->tail;
    }
    p->tail = l;
}

int dequeue(list *Q) {
    if (*Q == NULL) {
        return -1;
    }
    list l = *Q;
    int x = l->head;
    *Q = l->tail;
    free(l);
    return x;
}

int queue_peek(list Q) {
    if (Q == NULL) {
        return -1;
    }
    return Q->head;
}

#define SIZE 10

int hash(char key[], int size) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % size;
}

void insert(int T[], char key[], int value) {
    T[hash(key, SIZE)] = value;
}

int lookup(int T[], char key[]) {
    return T[hash(key, SIZE)];
}

void delete(int T[], char key[]) {
    T[hash(key, SIZE)] = -1;
}

//void main() {
    // test stack :
    /*int N = 5;
    int S[5];
    int n = 0;

    stack_push(S, N, &n, 10);
    stack_push(S, N, &n, 20);
    stack_push(S, N, &n, 30);

    printf("%i\n", stack_peek(S, n));*/

    // test queue :

    /*list Q = NULL;

    enqueue(&Q, 15);
    enqueue(&Q, 7);

    printf("Avant : %d\n", queue_peek(Q));
    printf("Dequeue : %d\n", dequeue(&Q));
    printf("Avant : %d\n", queue_peek(Q));*/

    /*int T[SIZE];
    for (int i = 0; i < SIZE; i++) {
        T[i] = -1;
    }

    insert(T, "abc", 42);
    insert(T, "xyz", 7);

    printf("%d\n", lookup(T, "abc"));
    printf("%d\n", lookup(T, "xyz"));

    delete(T, "abc");
    printf("%d\n", lookup(T, "abc"));*/

//}
