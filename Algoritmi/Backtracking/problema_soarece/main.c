#include <stdio.h>
#include <stdlib.h>

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
int is, js, ib, jb;



void cautare(int **a, int n, int m, int i, int j, int *cnt) {
    if (i >= n || j >= m || i < 0 || j < 0 || a[i][j] != 0) {
        return;
    }
    if (i == ib && j == jb) {
        *cnt = *cnt + 1;
    }
    else {
        a[i][j] = 2;
        for (int k = 0; k < 4; k++) {
            cautare(a, n, m, i + dx[k], j + dy[k], cnt);
        }
        a[i][j] = 0;
    }

}

void eliberare(int **a, int n) {
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
}

void afisare(int **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int n, m;
    if (argc != 3) {
        printf("Number of arguments is incorrect\n");
        exit(1);
    }
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Input file error\n");
        exit(1);
    }
    FILE *out = fopen(argv[2], "w");

    if (out == NULL) {
        printf("Output file error\n");
        exit(1);
    }
    fscanf(in,"%d %d", &n, &m);
    int **a = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int) * m);
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            fscanf(in,"%d", &a[i][j]);
        }
    }

    fscanf(in, "%d %d %d %d", &is, &js, &ib, &jb);

    // afisare(a, n, m);
    int cnt = 0;
    cautare(a, n, m, is, js, &cnt);
    fprintf(out, "%d\n", cnt);
    if (*a != NULL) {
        eliberare(a, n);
    }
    fclose(in);
    fclose(out);

    return 0;
}
