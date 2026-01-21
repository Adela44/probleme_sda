#include <stdio.h>
#include <stdlib.h>
#define val_minim INT_MAX

typedef struct Matrice {
    int **a;
    int n, m;
}Matrice;

typedef struct Solutie {
    int nr_sol;
    int minim_bloc;
    int x, y, margine;
}Sol;

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};

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

int valid(Sol *sol, Matrice *mat, int i, int j) {
    if (i < 0 || i >= mat->n || j < 0 || j >= mat->m) {
        return 0;
    }
    if (mat->a[i][j] != 1) {
        return 0;
    }
    return 1;
}

void Bk(Matrice *mat, int i, int j, int *cnt, Sol *s) {
    if (!valid(s, mat, i, j)) {
        return;
    }
    if (i == 0 || j == 0 || i == mat->n - 1 || j == mat->m - 1) {
        s->margine = 1;
    }

    (*cnt)++;
    mat->a[i][j] = 2;

    for (int k = 0; k < 4; k++) {
         Bk(mat, i + di[k], j + dj[k], cnt, s);
    }
    mat->a[i][j] = 1;

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
    Sol s;
    s.nr_sol = 0;
    s.minim_bloc = val_minim;

    for (int i = 0; i < mat->n; i ++) {  //dupa modul in care parcurgem matricea, mereu vom incepe din coltul cel mai stanga sus
        for (int j = 0; j < mat->m; j ++) {
            if (mat->a[i][j] == 1) {
                s.margine = 0;
                int cnt = 0;
                Bk(mat, i, j, &cnt, &s);
                if (!s.margine && cnt > 3) {
                        s.nr_sol++;
                    if (cnt < s.minim_bloc) {
                        s.minim_bloc = cnt;
                        s.x = i;
                        s.y = j;
                    }
                }
            }
        }
    }

    printf("Nr solutii: %d\nCurba minima: %d\nCoord cele mai stg sus x:%d, y%d\n", s.nr_sol, s.minim_bloc, s.x, s.y);

    fclose(f);
    eliberare_matrice(mat);
    free(mat);
    return 0;
}