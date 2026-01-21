#include <stdio.h>
#include <stdlib.h>


const int dx[] = {-2,-2,-1,-1,1, 1,2, 2};
const int dy[] = {1, -1, 2,-2,2,-2,1,-1};

typedef struct Matrice {
    int **a, **b, **c;
    int n, m;
}Matrice;

void copiere_sol(Matrice mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j++) {
            mat.c[i][j] = mat.b[i][j];
        }
    }
}

void Bk(Matrice mat, int i, int j, int pas) {
    static int maxi = -1;
    if (i < 0 || j < 0 || i >= mat.n || j >= mat.m || mat.a[i][j] != 0 || mat.b[i][j] != 0) {
        return;
    }
    mat.b[i][j] = pas;
    if (i == mat.n-1 && j == mat.m-1) {
        if (pas > maxi) {
            maxi = pas;
            copiere_sol(mat);
        }
    }
    else {
        for (int k = 0; k < 8; k++) {
            Bk(mat, i+dx[k], j+dy[k], pas+1);
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

void citire_matrice(FILE *f, Matrice mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j ++) {
            fscanf(f,"%d", &mat.a[i][j]);
        }
    }
}

void afisare_sol(FILE *out, Matrice mat) {
    if (mat.c == NULL) {
        printf("Nu exista solutie\n");
        exit(1);
    }
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.m; j++) {
            fprintf(out,"%d ",mat.c[i][j]);
        }
        fprintf(out,"\n");
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

    citire_matrice(in, mat);

    Bk(mat, 0,0,1);
    afisare_sol(out, mat);
    eliberare(mat.a, mat.n);
    eliberare(mat.b, mat.n);
    eliberare(mat.c, mat.n);
    fclose(in);   //ar trebui verificat si fclose
    fclose(out);
    return 0;
}