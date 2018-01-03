#include<stdio.h>

int p[200][201];

int e[200][200];
int o[200][200];

void do_case(int t) {

    int N;
    scanf("%i", &N);

    for(int i = 0; i < N; ++i) {

        p[i][0] = 0;

        for(int j = 1; j <= N; ++j) {
            int b;
            scanf("%i", &b);

            p[i][j] = (p[i][j-1]+b)%2;
        }
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            e[i][j] = 0;
            o[i][j] = 0;
        }
    }

    int c = 0;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = j; k < N; ++k) {
                e[j][k]++;

                if(p[i][j] != p[i][k+1]) {
                    int tmp = o[j][k];
                    o[j][k] = e[j][k];
                    e[j][k] = tmp;
                }

                c += e[j][k];
            }
        }
    }

    printf("%i\n", c);
}

int main() {
    int t;
    scanf("%i", &t);

    for(; t; t--) {
        do_case(t);
    }

    return 0;
}
