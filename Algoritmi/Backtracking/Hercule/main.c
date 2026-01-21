#include <stdio.h>
#include <stdlib.h>

typedef struct Matrice {
    int n, m;
    int a[11][11], b[11][11];
}Matrice;

const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};

void afisare_matrice(int a[][11], int n, int m);

void Bk(Matrice *mat, int i, int j, int pas, int *cnt) {
    if (i < 0 || j < 0 || i >= mat->n || j >= mat->m) {
        return;
    }

    if (mat->a[i][j] < pas || mat->b[i][j] != 0) {
        return;
    }

    mat->b[i][j] = pas;

    if (i == mat->n-1 && j == mat->m-1) {
        (*cnt)++;
        //afisare_matrice(mat->b, mat->n, mat->m);
    }
    else {
        for (int k = 0; k < 4; k ++) {
            Bk(mat, i+di[k], j+dj[k], pas + 1, cnt);
        }
    }
    mat->b[i][j] = 0;
}


void afisare_matrice(int a[][11], int n, int m) {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void init_matrice(Matrice *mat) {
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            mat->b[i][j] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Nr incorect de argumente\n");
        exit(1);
    }
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    Matrice *mat = (Matrice *) calloc(1, sizeof(Matrice));
    if (mat == NULL) {
        perror("calloc");
        exit(1);
    }
    fscanf(in, "%d %d", &mat->n, &mat->m);
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            fscanf(in,"%d", &mat->a[i][j]);
        }
    }
    afisare_matrice(mat->a, mat->n, mat->m);
    init_matrice(mat);
    int cnt = 0;
    Bk(mat, 0,0,1, &cnt);
    fprintf(out, "%d", cnt);
    free(mat);
    fclose(in);
    fclose(out);
    return 0;
}
