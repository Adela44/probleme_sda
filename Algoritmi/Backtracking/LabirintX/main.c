#include <stdio.h>
#include <stdlib.h>

const int di[] = {1, -1, 0, 0};
const int dj[] = {0, 0, 1, -1};

void eliberare(int **a, int m) {
    for (int i = 0; i < m; i ++) {
        free(a[i]);
    }
    free(a);
}

//tip 1 -> insula; tip2 -> peninsula

void Bk(int **a, int n, int m, int i, int j, int aux[]) {
    if (i < 0 || i >= m || j < 0 || j >= n)
        return;

    if (a[i][j] != 1)
        return;

    a[i][j] = 2; //marcam celulele vizitate

    if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
        aux[1] = 2;
    }

    aux[0] = aux[0] + 1;
    for (int k = 0; k < 4; k ++) {
        Bk(a, n, m, i + di[k], j + dj[k],  aux);
    }

    a[i][j] = 1;

}

void afisare(int **a, int m, int n) {
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Nr incorect de argumente");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    int n, m;
    fscanf(f, "%d %d", &m, &n);
    int **a = malloc(m * sizeof(int *));
    if (a == NULL) {
        printf("Eroare la malloc\n");
        exit(1);
    }
    for (int i = 0; i < m; i++) {
        a[i] = malloc(n * sizeof(int));
        if (a[i] == NULL) {
            printf("Eroare la malloc\n");
            exit(1);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j ++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }

    int aux[2];
    int maxi = -1; //aria maxima a unei insule
    int maxp = -1; //aria maxima a unei peninsule


    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            if (a[i][j] == 1) {
                aux[0] = 0; //cnt
                aux[1] = 1; //tipul
                Bk(a, n, m, i, j, aux);
                if (aux[0] > 0) {
                   if (aux[1] == 1) {
                       if (aux[0] > maxi) {
                           maxi = aux[0];
                       }
                   }
                   else {
                        if (aux[0] > maxp) {
                            maxp = aux[0];
                        }
                    }
                }
            }
        }
    }
    printf("%d %d", maxi, maxp);
    eliberare(a, m);
    fclose(f);
    return 0;
}