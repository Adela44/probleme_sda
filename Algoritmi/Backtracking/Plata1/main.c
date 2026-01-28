#include <stdio.h>
#include <stdlib.h>
#define maxi 6

/*
   Se consideră n tipuri de bancnote, cu valorile v[1] v[2] ... v[n], ordonate strict crescător.
   Pentru fiecare tip de bancnote se știe numărul de bancnote disponibile c[1] c[2] ... c[n].
   Determinati modalitatile de a plăti integral o sumă dată S cu bancnotele disponibile.

   Obs:
    1 ≤ n ≤ 6
    1 ≤ S ≤ 1000
    1 ≤ v[i] ≤ 100
    1 ≤ c[i] ≤ 10

 */

/*
   De ce problema se poate rezolva cu backtracking ?
    - solutie x[] poate fi reprez sub forma unui tablou
    - dimensiunea tabloului x[] este finita (stabilita de n, citit din fisier -> finit)
    - x[i] are un nr finit de valori posibile ( <= S, unde 0 <= S <= 1000, conform enuntului)
 */

typedef struct Plata {
    int v[maxi], c[maxi], x[maxi];
}Plata;


void afisare(int k, Plata *p, FILE *out) {
    for (int i = 0; i <= k; i ++) {
        fprintf(out,"%d ", p->x[i]);
    }
    fprintf(out, "\n");
}

int valid(Plata *p, int  k, int sum, int S) {
    if (sum + p->x[k] * p->v[k] <= S) { //e valid daca suma nr_banconta_curent * val_bancnota <= S
        return 1;
    }
    return 0;
}

int solutie(Plata *p, int k, int sum, int S) {
    return ((sum + p->x[k] * p->v[k]) == S); //daca am ajuns la suma dorita -> solutie
}

void Bk(Plata *p, int k, int n, int S, int sum, FILE *out) {
    if (k < n) {
        for (int i = 0; i <= p->c[k]; i ++) { //putem sa folosim o bacnota de un nr de ori (inclusiv 0)
            p->x[k] = i;  //ii dam la x[k] o val posibila a nr de bacnota
            if (valid(p, k, sum, S)) {
                if (solutie(p, k, sum, S)) {
                    afisare(k, p, out);
                }
                else {
                   Bk(p, k + 1, n, S, sum + p->x[k] * p->v[k], out); //suma e prea mica, adunam nr_banconta_curent * val_bancnota
               }                                                //si trecem pe urm poz, k + 1
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Eroare la citirea din fisier\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Eroare fisier citire");
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Eroare fisier output");
        exit(1);
    }
    int n, S;
    fscanf(f, "%d %d", &n, &S);
    Plata p;
    for (int i = 0; i < n; i ++) {
        fscanf(f, "%d", &p.v[i]);
    }
    for (int i = 0; i < n; i ++) {
        fscanf(f, "%d", &p.c[i]);
    }

    Bk(&p, 0, n, S, 0, out);

    fclose(f);
    fclose(out);
}