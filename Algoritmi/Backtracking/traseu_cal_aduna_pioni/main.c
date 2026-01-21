#include <stdio.h>
#include <stdlib.h>

/*
  2 - cal
  3 - nebun
  1 - pion
  Nebunii trebuie ignorati, nu luati si se incheie cand calul a luat ultimul pion
  Exista cel putin un pion pe tabla
 */

const int dx[] = {-2,-2,-1,-1,1, 1,2, 2};
const int dy[] = {1, -1, 2,-2,2,-2,1,-1};

typedef struct Matrice {
    int **a, **b, **c;
    int n, m;
}Matrice;


void actualizare_date(FILE *out);

void Bk(Matrice mat, int i, int j, int pas, int *pas_min, int nr_pioni, int *nr_sol) {
    if (i < 0 || j < 0 || i >= mat.n || j >= mat.m) {
        return;
    }
    if (mat.a[i][j] == 3 || mat.b[i][j] != 0 || (mat.a[i][j] == 2 && mat.b[i][j] != 0)) {
        return;
    }

    mat.b[i][j] = pas;

    if (mat.a[i][j] == 1)
        nr_pioni--;

    if (nr_pioni == 0) {
        if (pas < *pas_min) {
            *pas_min = pas;
        }
        (*nr_sol)++;
    }
    else {
        for (int k = 0; k < 8; k ++) {
            Bk(mat, i + dx[k], j + dy[k], pas + 1, pas_min, nr_pioni, nr_sol);
        }
    }
    mat.b[i][j] = 0;

}


void eliberare(int **a, int n) {
    for (int i = 0; i < n; i ++) {
        free(a[i]);
    }
    free(a);
}

void verificare_fisier(FILE *f) {
    if (f == NULL) {
        fprintf(stderr, "Eroare fisier\n");
        exit(1);
    }
}

void citire_matrice(FILE *f, Matrice mat, int *nr_pioni, int *x, int *y) {
    if (mat.a != NULL) {
        for (int i = 0; i < mat.n; i++) {
            for (int j = 0; j < mat.m; j ++) {
                fscanf(f,"%d", &mat.a[i][j]);
                if (mat.a[i][j] == 1) {
                    *nr_pioni += 1;
                }
                if (mat.a[i][j] == 2) {
                    *x = i;
                    *y = j;
                }
            }
        }
    }
}



int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Nr insuficient de argumente\n");
        exit(1);
    }
    FILE *in = fopen(argv[1], "r");
    verificare_fisier(in);
    FILE *out = fopen(argv[2], "w");
    verificare_fisier(out);

    //alocare in memorie matrici
    Matrice mat;
    fscanf(in,"%d %d", &mat.n, &mat.m);   //ar trebui verificat si malloc
    mat.a = malloc(sizeof(int *) * mat.n);
    mat.c = malloc(sizeof(int *) * mat.n);
    mat.b = calloc(mat.n, sizeof(int *));
    for (int i = 0; i < mat.n; i++) {
        mat.a[i] = malloc(sizeof(int) * mat.m);
        mat.c[i] = malloc(sizeof(int) * mat.m);
        mat.b[i] = calloc(mat.m, sizeof(int));
    }
    int nr_pioni = 0;
    int x, y;
    citire_matrice(in, mat, &nr_pioni, &x, &y); //cautam in acelasi timp poz pe care se afla calul si numaram pionii

    int pas_min = 10000;
    int nr_sol = 0;
    if (mat.a != NULL && mat.b != NULL) {
        Bk(mat, x,y,1,&pas_min, nr_pioni,&nr_sol);
    }
    fprintf(out, "Nr min de pasi: %d\nNr de solutii: %d\n", nr_pioni, nr_sol);
    eliberare(mat.a, mat.n);
    eliberare(mat.b, mat.n);
    eliberare(mat.c, mat.n);
    fclose(in);   //ar trebui verificat si fclose
    fclose(out);
    return 0;
}