#include <stdio.h>
#include <stdlib.h>


const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};


typedef struct Matrice {
    int **a;
    int n, m;
}Matrice;

void citire_matrice(Matrice *mat, FILE *f) {
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            fscanf(f, "%d", &mat->a[i][j]);
        }
    }
}

void eliberare_matrice(Matrice *mat) {
    for (int i = 0; i < mat->n; i++) {
        free(mat->a[i]);
    }
    free(mat->a);
}

void Bk(Matrice *mat, int i, int j, int *cnt, int *margine) {
    if (i < 0 || i >= mat->n || j < 0 || j >= mat->m) {
        return;
    }
    if (mat->a[i][j] != 1) {
        return;
    }
    /*
    if (i == 0 || j == 0 || i == mat->n - 1 || j == mat->m - 1) {
        *margine = 1;
    }
    */
    (*cnt)++;
    mat->a[i][j] = *cnt + 1;
    for (int k = 0; k < 4; k ++) {
        Bk(mat, i + di[k], j + dj[k], cnt, margine);
    }
   // mat->a[i][j] = 1;  //ca sa imi numere valorile de 1 si sa ramana
}

void afisare_matrice(Matrice *mat) {
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            if (mat->a[i][j] > 0) {
                mat->a[i][j] -= 1;
            }
            printf("%d ", mat->a[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "argument error");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("open error");
        exit(1);
    }
    Matrice *mat = (Matrice *) malloc(sizeof(Matrice));
    fscanf(f, "%d %d", &mat->n, &mat->m);
    mat->a = malloc( sizeof(int *) * mat->n);
    if (mat->a == NULL) {
        perror("malloc error");
        exit(1);
    }
    for (int i = 0; i < mat->n; i++) {
        mat->a[i] = (int *) malloc(sizeof(int) * mat->m);
        if (mat->a[i] == NULL) {
            perror("malloc error");
            exit(1);
        }
    }
    citire_matrice(mat, f);

    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            if (mat->a[i][j] == 1) {
                int cnt = 0;
                int margine = 0;
                Bk(mat, i, j, &cnt, &margine);
                if (!margine && cnt > 3) {
                    printf("Cnt: %d\n", cnt);
                    afisare_matrice(mat);
                }
            }
        }
    }


    eliberare_matrice(mat);
    free(mat);
    fclose(f);
    return 0;
}