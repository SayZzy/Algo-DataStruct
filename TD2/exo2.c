#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int is_sorted_ascending(int A[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (A[i] > A[i + 1]) return 0;
    return 1;
}

void copy_array(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}


void selection_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (A[j] < A[min]) min = j;
        swap_int(&A[i], &A[min]);
    }
}


void insertion_sort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}


void bubble_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (A[j] > A[j + 1])
                swap_int(&A[j], &A[j + 1]);
}


void merge(int A[], int tmp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) tmp[k++] = A[i++];
        else              tmp[k++] = A[j++];
    }
    while (i <= mid)   tmp[k++] = A[i++];
    while (j <= right) tmp[k++] = A[j++];
    for (k = left; k <= right; k++)
        A[k] = tmp[k];
}

void merge_sort_rec(int A[], int tmp[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge_sort_rec(A, tmp, left, mid);
    merge_sort_rec(A, tmp, mid + 1, right);
    merge(A, tmp, left, mid, right);
}

void merge_sort(int A[], int n) {
    int *tmp = malloc(n * sizeof(int));
    merge_sort_rec(A, tmp, 0, n - 1);
    free(tmp);
}


int partition(int A[], int left, int right) {
    int pivot = A[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
        if (A[j] <= pivot)
            swap_int(&A[++i], &A[j]);
    swap_int(&A[i + 1], &A[right]);
    return i + 1;
}

void quick_sort_rec(int A[], int left, int right) {
    if (left >= right) return;
    int p = partition(A, left, right);
    quick_sort_rec(A, left, p - 1);
    quick_sort_rec(A, p + 1, right);
}

void quick_sort(int A[], int n) {
    quick_sort_rec(A, 0, n - 1);
}


double mesurer(void (*tri)(int[], int), int original[], int copie[], int n) {
    copy_array(original, copie, n);
    clock_t debut = clock();
    tri(copie, n);
    clock_t fin = clock();
    if (!is_sorted_ascending(copie, n))
        printf("ERREUR : tableau non trie !\n");
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main(void) {
    int tailles[] = {1000, 5000, 10000, 50000};
    int nb = sizeof(tailles) / sizeof(tailles[0]);

    srand((unsigned)time(NULL));
    printf("%8s %10s %10s %10s %10s %10s\n",
           "n", "selection", "insertion", "bubble", "merge", "quick");

    for (int t = 0; t < nb; t++) {
        int n = tailles[t];
        int *original = malloc(n * sizeof(int));
        int *copie = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            original[i] = rand() % 1000001;

        printf("%8d %10.4f %10.4f %10.4f %10.4f %10.4f\n", n,
               mesurer(selection_sort, original, copie, n),
               mesurer(insertion_sort, original, copie, n),
               mesurer(bubble_sort,    original, copie, n),
               mesurer(merge_sort,     original, copie, n),
               mesurer(quick_sort,     original, copie, n));

        free(original);
        free(copie);
    }
    return 0;
}