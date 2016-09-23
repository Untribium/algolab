#include<stdio.h>

int max(int i, int j) {
    return (i > j) ? i : j;
}

void do_case() {
    int N;
    scanf("%i", &N);

    int pos, n, h;

    for(pos = 0, n = 0; n < N; n++) {
        scanf("%i", &h);

        if(!pos || pos > n) {
            pos = max(pos, n+h);
        }
        else {
            break;
        }
    }

    printf("%i\n", n);

    while(++n < N) {
        scanf("%d", &h);
    }
}

int main() {
    int t;
    scanf("%i", &t);

    for(; t; t--) {
        do_case();
    }

    return 0;
}
