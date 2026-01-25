#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Nr matricol -> Materie -> Note
  Nr matricol e unic, un student poate avea mai multe materii si la fiecare materie pot exista mai multe note:
  Ex in date.txt

             AC -> 6.4, 7.8
              |
 LM614330 -> SDA -> 4.5
     |
 LM613400 -> AC -> 5


 */

typedef struct note {
    double val;
    struct note *next;
}note;

typedef struct materie {
    char denumire[21];
    struct materie *next;
    note *n;
}materie;

typedef struct student {
    char marca[9];
    struct student *next;
    materie *m;
}student;


void print_nota(note *not) {
    while (not != NULL) {
        printf("%.2f, ", not->val);
        not = not->next;
    }
}

void print_materie(materie *mat) {
    while (mat != NULL) {
        printf(" %s ", mat->denumire);
        print_nota(mat->n);
        mat = mat->next;
    }
}

void print_student(student *st, int *cnt) {
    while (st != NULL) {
        printf("%s: ", st->marca);
        print_materie(st->m);
        printf("\n");
        st = st->next;
        *cnt = *cnt + 1;
    }
}

void adauga_nota(note *not, double valoare);
materie * exista_materie(materie *mat, char *den);

void adauga_nota(note *not, double valoare) {
    note *aux = not;
    while (aux->next != NULL) {
        aux = not->next;
    }
    aux->next = malloc(sizeof(note));
    aux->next->val = valoare;
    aux->next->next = NULL;
}

materie * exista_materie(materie *mat, char *den) {
    while (mat != NULL) {
        if (strcmp(mat->denumire, den) == 0) {
            return mat;
        }
        mat = mat->next;
    }
    return NULL;
}

void adaugare(student **head, char *nr_matricol, char *subiect, double valoare)
{
    student *p = *head;
    student *last = NULL;
    materie *noua_materie = NULL;

    while (p != NULL) {
        if (strcmp(p->marca, nr_matricol) == 0) {

            materie *aux_m = exista_materie(p->m, subiect); //verificam daca exista materia
            if (aux_m != NULL) { //daca deja exista, adaugam direct nota
                adauga_nota(aux_m->n, valoare);
            }
            else {
                noua_materie = malloc(sizeof(materie));
                strcpy(noua_materie->denumire, subiect);
                noua_materie->next = NULL;

                noua_materie->n = malloc(sizeof(note));
                noua_materie->n->val = valoare;
                noua_materie->n->next = NULL;

                aux_m = p->m; //parcurgem lista pana la ult elem, sa adaugam
                while (aux_m->next != NULL) {
                    aux_m = aux_m->next;
                }
                aux_m->next = noua_materie;
                aux_m->next->n = noua_materie->n;

            }
            return;
        }
        last = p;
        p = p -> next;
    }
    //daca nu exista inca studentul
    student *nou = malloc(sizeof(student));
    strcpy(nou->marca, nr_matricol);
    nou->next = NULL;

    nou->m = malloc(sizeof(materie));
    strcpy(nou->m->denumire, subiect);
    nou->m->next = NULL;

    nou->m->n = malloc(sizeof(note));
    nou->m->n->val = valoare;
    nou->m->n->next = NULL;

    if (*head == NULL) {
        *head = nou;
    }
    else {
        last->next = nou;
    }
}

void eliberare_note(note *n) {
    while (n != NULL) {
        note *aux = n;
        n = n->next;
        free(aux);
    }
}

void eliberare_materie(materie *mat) {
    while (mat != NULL) {
        materie *aux = mat;
        mat = mat->next;
        eliberare_note(aux->n);
        free(aux);
    }
}

void eliberare_student(student *st) {
    while (st != NULL) {
        student *aux = st;
        st = st->next;
        eliberare_materie(aux->m);
        free(aux);
    }
}

void swap(student *a, student *b) {
    student aux = *a;
    *a = *b;
    *b = aux;
}

void quicksort(student a[], int prim, int ultim) {
    int stanga = prim + 1;
    int dreapta = ultim;

    //alegere pivot
    swap(&a[prim], &a[(prim + ultim) / 2]);

    //mutare pivot pe prima pozitie
    student pivot = a[prim];
    while (stanga <= dreapta) {
        while (strcmp(a[stanga].marca, pivot.marca) < 0) stanga++;
        while (strcmp(a[dreapta].marca, pivot.marca) > 0) dreapta--;

        if (stanga < dreapta)
            swap(&a[stanga++], &a[dreapta--]);
        else
            stanga++;
    }
    swap(&a[dreapta], &a[prim]);

    if (prim < dreapta - 1)
        quicksort(a, prim, dreapta - 1);
    if (dreapta + 1 < ultim)
        quicksort(a, dreapta + 1, ultim);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Nr argumente gresit\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Eroare fisier");
        exit(1);
    }
    int n;
    fscanf(f,"%d", &n);
    getc(f); //'\n'
    char materie[21], marca[9];
    double nota;

    student *head = NULL;

    for (int i = 0; i < n; i ++) {
        char sir[100];
        char *aux = fgets(sir, 100, f);
        if (aux != NULL) {
            sscanf(sir, "%20s %8s %lf", marca, materie, &nota);
            //printf("%s %s %.02f\n", materie,marca, nota);
            adaugare(&head, marca, materie, nota);
        }
    }
    int cnt = 0;
    print_student(head, &cnt);
    student *aux = head;
    printf("Numarul studentilor: %d\n", cnt);
    student *matrice = malloc(sizeof(student) * cnt);
    for (int i = 0; i < cnt; i ++) {
        matrice[i] = *aux;
        aux = aux->next;
    }
   // printf("%lf\n", matrice[2].m->n->val);
    quicksort(matrice, 0, cnt-1); //crescator dupa nr matricol
    for (int i = 0; i < cnt; i ++) {
        printf("%d: %s ", i, matrice[i].marca);
        print_materie(matrice[i].m);
        printf("\n");
    }
    free(matrice);
    eliberare_student(head);
    fclose(f);
    return 0;
}