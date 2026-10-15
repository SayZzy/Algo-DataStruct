#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int est_premier(int k)
{
    if (k < 2)
        return 0;
    for (int d = 2; d * d <= k; d++)
    {
        if (k % d == 0)
            return 0;
    }
    return 1;
}

int premiers_naive(int n)
{
    int compteur = 0;
    for (int k = 2; k < n; k++)
    {
        if (est_premier(k))
            compteur++;
    }
    return compteur;
}

int premiers_fast(int n)
{
    char *tab = malloc(n * sizeof(char));
    if (tab == NULL)
        return -1;

    for (int i = 0; i < n; i++)
        tab[i] = 1;

    for (int p = 2; p * p < n; p++)
    {
        if (tab[p] == 1)
        {
            for (int m = p * p; m < n; m += p)
                tab[m] = 0;
        }
    }

    int compteur = 0;
    for (int k = 2; k < n; k++)
    {
        if (tab[k] == 1)
            compteur++;
    }
    free(tab);
    return compteur;
}

int main()
{
    int n = 1000000;

    clock_t start = clock();
    printf("%i\n", premiers_naive(n));
    clock_t end = clock();
    double temps_naive = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Temps naive : %f \n", temps_naive);

    clock_t startc = clock();
    printf("%i\n", premiers_fast(n));
    clock_t endc = clock();
    double temps_crible = (double)(endc - startc) / CLOCKS_PER_SEC;
    printf("Temps crible : %f \n", temps_crible);

    return 0;
}