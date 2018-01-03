#include<stdio.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &t);

    while(T--) {
        int m;
        scanf("%d", &m);

        double v, sum = 0;

        while(m) {
            scanf("%lf", &v);
            sum += v;

            m--;
        }

        printf("%lf\n", sum);
    }
}
