#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

bool is_sorted_increasing(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] >= a[i + 1]) {
            return false;
        }
    }
    return true;
}

bool linear_search(int A[], int n, int target)
{
    for(int i = 0; i < n; i++)
    {
        if(A[i] == target)
        {
            return true;
        }
    }
    return false;
}

bool jump_search(int A[], int n, int target)
{
    if(is_sorted_increasing(A, n) == 1)
    {
        int jump = (int)sqrt(n);
        int prev = 0;
        int cur = jump;
        while (cur < n && A[cur - 1] < target) {
            prev = cur;
            cur += jump;
        }

        int end = (cur < n) ? cur : n;
        for (int i = prev; i < end; i++) {
            if (A[i] == target) {
                return true;
            }
            if (A[i] > target) {
                return false;
            }
        }
    }
    return false;
}

bool binary_search(int A[], int n, int target)
{
    if(is_sorted_increasing(A, n) == false)
    {
        return -1;
    }

    int max = n - 1;
    int min = 0;

    while(min <= max)
    {
        int mid = (int)((min + max) / 2);
        if(target == A[mid])
        {
            return true;
        }
        else if(target < A[mid])
        {
            max = mid - 1;
        }
        else if(target > A[mid])
        {
            min = mid + 1;
        }
    }
    return false;
}


#define N 10000

int sorted_arr[N];
int unsorted_arr[N];

void init_arrays(void) {
    // Tableau trié : 3, 6, 9, ..., 30000 (multiples de 3, strictement croissant)
    for (int i = 0; i < N; i++) {
        sorted_arr[i] = 3 * (i + 1);
    }

    // Tableau non trié : copie du tableau trié, puis quelques échanges
    for (int i = 0; i < N; i++) {
        unsorted_arr[i] = sorted_arr[i];
    }

    int tmp;
    tmp = unsorted_arr[0];     unsorted_arr[0]     = unsorted_arr[4999]; unsorted_arr[4999] = tmp;
    tmp = unsorted_arr[10];    unsorted_arr[10]    = unsorted_arr[9000]; unsorted_arr[9000] = tmp;
    tmp = unsorted_arr[2500];  unsorted_arr[2500]  = unsorted_arr[7500]; unsorted_arr[7500] = tmp;
}

void main()
{
    printf("Is sorted a : %d\n", is_sorted_increasing(sorted_arr, N));
    printf("Is sorted b : %d\n", is_sorted_increasing(unsorted_arr, N));


    clock_t start = clock();
    printf("Linear search a : %d\n", linear_search(sorted_arr, N, 15000));
    clock_t end = clock();
    double temps_linear = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Temps linear : %f \n", temps_linear);

    clock_t start2 = clock();
    printf("Jump search a : %d\n", jump_search(sorted_arr, N, 15000));
    clock_t end2 = clock();
    double temps_jump = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("Temps jump : %f \n", temps_jump);

    clock_t start3 = clock();
    printf("Binary search a : %d\n", binary_search(sorted_arr, N, 15000));
    clock_t end3 = clock();
    double temps_binary = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf("Temps binary : %f \n", temps_binary);
}