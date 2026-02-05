#include <stdio.h>


int Divide(int *a, int st, int dr) {
    if (st == dr) {
        return ((a[st] % 2) != 0);
    }
    else {
        int m = (st + dr) / 2;
        int s1 = Divide(a, st, m);
        int s2 = Divide(a, m + 1, dr);
        return s1 + s2;
    }
}

int main(void) {
    int n, a[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
    }
    int s = Divide(a, 0, n - 1);
    if (s > 0) {
        printf("DA");
    }
    else {
        printf("NU");
    }
    return 0;
}