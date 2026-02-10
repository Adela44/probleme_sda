#include <stdio.h>
#include <stdlib.h>
#define maxi 30 //capacitatea cozii
#define MAX_ST 100

typedef struct Rezervare{
    int id;
    int zbor;
    int prioritate;
    int pret;
}Rezervare;

typedef struct Zbor {
    int cod;
    int capacitate;
    struct Zbor *next;
    Rezervare q[maxi];
}Zbor;

Rezervare stiva[MAX_ST]; //stiva globala



void recursivitate(Rezervare *rez, int i, int *sum, int *nr, int P, int n) {
    if (i == n) {
        return;
    }
    if (rez[i].prioritate <= P) {
        *sum = *sum + rez[i].pret;
        *nr = *nr + 1;
    }
    recursivitate(rez, i + 1, sum, nr, P, n);
}


void adaugare(Zbor **front, Rezervare *rez, int n) {
    Zbor *aux = *front;
    if (aux == NULL) { //suntem la primul element
        aux = malloc(sizeof(Zbor));
        aux->cod = rez[0].zbor;
        aux->capacitate = 0;
        aux->q[aux->capacitate] = rez[0];
        aux->next = NULL;
        *front = aux;
    }
    for (int i = 1; i < n; i ++) {
        if (aux->cod == rez[i].zbor) {
            aux->capacitate++;
            aux->q[aux->capacitate] = rez[i];
        }
        else {
            aux->next = malloc(sizeof(Zbor));
            aux = aux->next;
            aux->cod = rez[i].zbor;
            aux->capacitate = 0;
            aux->q[aux->capacitate] = rez[i];
            aux->next = NULL;
        }
    }
}

void eliberare(Zbor *front) {
    while (front != NULL) {
        Zbor *aux = front->next;
        free(front);
        front = aux;
    }
}


void afisare_lista(Zbor *front, Rezervare *rez, int n, FILE *out) {
    while (front != NULL) {
        fprintf(out,"%d:\n", front->cod);
        for (int i = 0; i <= front->capacitate; i ++) {
            fprintf(out, " %d %d %d\n", front->q[i].id, front->q[i].prioritate, front->q[i].pret);
        }
        front = front->next;
    }

}

void swap(Rezervare *a, Rezervare *b) {
    Rezervare aux = *a;
    *a = *b;
    *b = aux;
}


int conditie_zbor(int var, Rezervare a, Rezervare pivot) { //conditie subpunctul B
    if (var == 0) {
        if (a.zbor < pivot.zbor) {
            return 1;
        }
    }
    else {
        if (a.zbor > pivot.zbor) {
            return 1;
        }
    }
    return 0;
}

int conditie_prioritate_pret(int var, Rezervare a, Rezervare pivot) { //conditie subpunctul A
    if (var == 0) { //suntem la i ++
        if (a.prioritate > pivot.prioritate) {
            return 1;
        }
        if (a.prioritate == pivot.prioritate && a.pret < pivot.pret) {
            return 1;
        }
    }
    else{   //suntem la j++
        if (a.prioritate < pivot.prioritate) {
            return 1;
        }
        if (a.prioritate == pivot.prioritate && a.pret > pivot.pret) {
            return 1;
        }
    }
    return 0;
}

void QuickSort(Rezervare *arr, int st, int dr, int (*func)(int, Rezervare, Rezervare)) {
    int i = st;
    int j = dr;

    Rezervare pivot = arr[(st + dr)/2];
    while (i <= j) {
        while (func(0, arr[i], pivot)) {
            i++;
        }
        while (func(1, arr[j], pivot)) {
            j--;
        }
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    if (st < j) {
        QuickSort(arr, st, j, func);
    }
    if (i < dr) {
        QuickSort(arr, i, dr, func);
    }
}

void afisare(Rezervare *arr, int n) {
    for (int i = 0; i < n; i ++) {
        printf("%d %d %d %d\n", arr[i].id,arr[i].zbor, arr[i].prioritate, arr[i].pret);
    }
    printf("\n");
}

void noua_stiva(Rezervare *rez, int n) {
    QuickSort(rez, 0, n-1, conditie_prioritate_pret);
    for (int i = 0; i < n; i ++) {
        stiva[i] = rez[i]; //iar top = n-1;
    }
}

void Greedy(int i, int P, int B, int *cnt) {
    if (i == 0) {
        return;
    }
    int sum = 0;
    int nr = 0;

    for (int j = i; j >= 0; j --){
        if (stiva[j].prioritate >= P) {
            if (sum + stiva[j].pret <= B) {
                sum += stiva[j].pret;
                nr++;
            }
        }
        else {
            break;
        }
    }
    if (*cnt < nr) {
        *cnt = nr;
    }
    Greedy(i-1, P, B, cnt);
}



int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Nr argumente incorect\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Fisier intrare");
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Fisier iesire");
        exit(1);
    }

    int n, B, P;
    fscanf(f,"%d %d %d", &n, &B, &P);

    Rezervare *rez = (Rezervare *)malloc(sizeof(Rezervare) * n);
    int id, zbor, prioritate, pret;
    for (int i = 0; i < n; i ++) {
       int aux =  fscanf(f, "%d %d %d %d", &id, &zbor, &prioritate, &pret);
        if (aux != 4) {
            fprintf(stderr, "Eroare la citirea din fisier\n");
            exit(1);
        }
        rez[i].id = id;
        rez[i].zbor = zbor;
        rez[i].prioritate = prioritate;
        rez[i].pret = pret;
    }
   // afisare(rez, n);
    QuickSort(rez, 0, n-1, conditie_prioritate_pret);
  //  afisare(rez, n);

    QuickSort(rez, 0, n-1, conditie_zbor);
  //  afisare(rez, n);

    Zbor *front = NULL;
    adaugare(&front, rez, n);
    fprintf(out, "LISTA - ZBOR:\n");
    afisare_lista(front, rez, n, out);

    QuickSort(rez, 0, n-1, conditie_prioritate_pret);

    eliberare(front);

    int sum = 0;
    int nr = 0;
    recursivitate(rez, 0, &sum, &nr, P, n);
    fprintf(out,"NR SI SUMA: %d, %d\n", nr, sum);

    noua_stiva(rez, n);
    int cnt = 0;
    Greedy(n-1, P, B, &cnt);
    fprintf(out,"GREEDY: %d", cnt);
    free(rez);
    fclose(f);
    fclose(out);
    return 0;
}