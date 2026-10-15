#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fibo_naive(int n)
{
    if (n == 0 || n == 1)
        return n;
    return fibo_naive(n - 1) + fibo_naive(n - 2);
}

int fibo_dyna(int n, int *array)
{
    if (n <= 1)
        return n;
    if (array[n] == -1)
        array[n] = fibo_dyna(n - 1, array) + fibo_dyna(n - 2, array);
    return array[n];
}

int main()
{
    int n = 13;
    int *arr = malloc((n + 1) * sizeof(int));
    if (arr == NULL)
        return 1;

    for (int i = 0; i <= n; i++)
        arr[i] = -1;

    clock_t start = clock();
    printf("%i\n", fibo_naive(n));
    clock_t end = clock();
    double temps_naive = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Temps naive : %f \n", temps_naive);

    clock_t startd = clock();
    printf("%i\n", fibo_dyna(n, arr));
    clock_t endd = clock();
    double temps_dyna = (double)(endd - startd) / CLOCKS_PER_SEC;
    printf("Temps dyna : %f \n", temps_dyna);

    return 0;
}