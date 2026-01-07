#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int di[] = {0,0,1,-1, 1, 1, -1, -1};
const int dj[] = {1,-1,0,0, -1, 1,  -1, 1};

typedef struct Matrice {
    int n, m;
    char a[21][21];
    char b[21][21];
    char sol[21][21];
}Matrice;
void afisare_matrice(char a[][21], int n, int m);

void copiere_sol(Matrice *mat) {
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j++) {
            mat->sol[i][j] = mat->b[i][j];
        }
    }
}

void Bk(Matrice *mat, int i, int j, int baterie, int pas) {
    static int minim = 10000;
    if (i < 0 || i >= mat->n || j < 0 || j >= mat->m) {
        return;
    }

    if (mat->a[i][j] == '*' || mat->b[i][j] != '.') {
        return;
    }

    if (baterie == 0 && mat->a[i][j] != 'E') {
        return;
    }
    mat->b[i][j] ='#';
    if (mat->a[i][j] == '+') {
        baterie += 10;
    }

    if (mat->a[i][j] == 'E') {
        if (pas < minim) {
            minim = pas;
            copiere_sol(mat);
        }
    }
    else {
        for (int k = 0; k < 8; k ++) {
            Bk(mat, i + di[k], j + dj[k], baterie - 1, pas + 1);
        }
    }
    mat->b[i][j] ='.';

}

void afisare_matrice(char a[][21], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}

void init_matrice(char b[][21], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[i][j] = '.';
        }
    }
}

void cautare_val(Matrice *mat, int *is, int *js) {
    for (int i = 0; i < mat->n; i++) {
        for (int j = 0; j < mat->m; j++) {
            if (mat->a[i][j] == 'S') {
                *is = i;
                *js = j;
                return;
            }
        }
    }
}

int main(int argc, char **argv) {
    //matricea poate fi de max 20x20
     if (argc != 2) {
         printf("Nr incorect de argumente\n");
         exit(1);
     }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    Matrice *mat = calloc(1, sizeof(Matrice));
    if (!mat) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    char aux[21];
   while (i < 21 && fgets(aux, sizeof(aux), f)) {
        aux[strcspn(aux, "\n")] = '\0';
        int len = (int)strlen(aux);
        for (int j = 0; j < len; j++) {
            mat->a[i][j] = aux[j];
        }
        mat->a[i][len] = '\0';
        if (mat->m == 0) {
            mat->m = len;
        }
        i++;
    }
    mat->n = i;
    init_matrice(mat->b, mat->n, mat->m);
    int is, js;
    cautare_val(mat, &is, &js);
    Bk(mat, is, js, 5, 1);
    afisare_matrice(mat->sol, mat->n, mat->m);
    free(mat);
    fclose(f);
    return 0;
}