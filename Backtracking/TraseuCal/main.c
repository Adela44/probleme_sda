#include <stdio.h>
#include <stdlib.h>


const int dx[] = {-2,-2,-1,-1,1, 1,2, 2};
const int dy[] = {1, -1, 2,-2,2,-2,1,-1};

void afisare_sol(FILE *out, int **b, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(out,"%d ", b[i][j]);
        }
        fprintf(out, "\n");
    }
}

void Bk(FILE *out, int **a, int **b, int n, int m, int i, int j, int pas, int *cnt) {
    if (i < 0 || j < 0 || i >= n || j >= m || a[i][j] != 0 || b[i][j] != 0) {
        return;
    }
    b[i][j] = pas;
    if (i == n-1 && j == m-1) {
        *cnt = *cnt + 1;
        if (*cnt == 1) {
            afisare_sol(out, b, n, m);
        }
    }
    else {
        for (int k = 0; k < 8; k++) {
            Bk(out, a, b, n, m, i+dx[k], j+dy[k], pas+1, cnt);
        }
    }
    b[i][j] = 0;
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

void citire_matrice(FILE *f, int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j ++) {
            fscanf(f,"%d", &a[i][j]);
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

    int n, m;
    fscanf(in,"%d %d", &n, &m);   //ar trebui verificat si malloc
    int **a = malloc(sizeof(int *) * n);
    int **b = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int) * m);
        b[i] = calloc(m, sizeof(int));
    }

    citire_matrice(in, a, n, m);

    int cnt = 0;
    Bk(out, a, b, n, m, 0,0,1, &cnt);
    fprintf(out, "Numarul solutiilor posibile: %d\n", cnt);
    eliberare(a, n);
    eliberare(b, n);
    fclose(in);   //ar trebui verificat si fclose
    fclose(out);
    return 0;
}