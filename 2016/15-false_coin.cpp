#include<stdio.h>

void do_case() {

    int n,k;
    scanf("%i", &n);
    scanf("%i", &k);

    char coins[n];
    for(int i = 0; i < n; ++i) {
        coins[i] = 'u';
    }

    for(int i = 0; i < k; ++i) {

        int p;
        scanf("%i", &p);

        int a[n];

        for(int j = 0; j < n; ++j) {
            a[j] = 0;
        }

        for(int j = 0; j < 2*p; ++j) {
            int c;
            scanf("%i", &c);

            a[c-1] = j/p+1;
        }

        char o;
        scanf(" %c", &o);

        char h[3];

        if(o == '=') {
            for(int j = 0; j < n; ++j) {
                if(a[j]) {
                    coins[j] = 0;
                }
            }
        }
        else {
            h[1] = (o == '<') ? '<' : '>';
            h[2] = (o == '<') ? '>' : '<';

            for(int j = 0; j < n; ++j) {

                if(!a[j]) {
                    coins[j] = 0;
                }
                if(coins[j] == 'u') {
                    coins[j] = h[a[j]];
                }
                else if(coins[j] != h[a[j]]) {
                    coins[j] = 0;
                }
            }
        }
    }

    int count = 0, v = 0;

    for(int i = 0; i < n; ++i) {
        if(coins[i]) {
            count++;
            v = i+1;
        }
    }

    if(count != 1) {
        v = 0;
    }

    printf("%i\n", v);
}

int main() {
    int t;
    scanf("%i", &t);

    for(; t; --t) {
        do_case();
    }

    return 0;
}
